FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV G4_VERSION=11.2.0

# 1. Instalar librerías de sistema y entorno gráfico (Qt/OpenGL)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ca-certificates \
    libxerces-c-dev \
    libexpat1-dev \
    libqt5opengl5-dev \
    qtbase5-dev \
    libxmu-dev \
    libxi-dev \
    nano \
    && rm -rf /var/lib/apt/lists/*

# 2. Descargar y compilar Geant4
WORKDIR /tmp
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v${G4_VERSION}/geant4-v${G4_VERSION}.tar.gz \
    && tar -xzf geant4-v${G4_VERSION}.tar.gz \
    && mkdir geant4-build && cd geant4-build \
    && cmake -DGEANT4_INSTALL_DATA=ON \
             -DGEANT4_USE_QT=ON \
             -DGEANT4_USE_OPENGL_X11=ON \
             -DGEANT4_BUILD_MULTITHREADED=ON \
             -DCMAKE_INSTALL_PREFIX=/opt/geant4 \
             ../geant4-v${G4_VERSION} \
    && make -j$(nproc) \
    && make install \
    && rm -rf /tmp/*

# 3. Requisito PDF: Crear la carpeta /geant4lab
RUN mkdir -p /geant4lab

# 4. Requisito PDF: Crear el script geant4make.sh global
RUN printf '#!/bin/bash\nsource /opt/geant4/bin/geant4.sh\necho "Entorno Geant4 cargado correctamente."\n' > /usr/local/bin/geant4make.sh \
    && chmod +x /usr/local/bin/geant4make.sh

# Cargar automáticamente el entorno en bash
RUN echo "source /usr/local/bin/geant4make.sh" >> /etc/bash.bashrc

# Copiar proyecto
COPY geant4lab /geant4lab

# 5. Limpiar cache antiguo, generar vis.mac completo con disparos de partículas y compilar el proyecto
RUN mkdir -p /geant4lab/proyecto_lluvias_cosmicas/build && \
    rm -rf /geant4lab/proyecto_lluvias_cosmicas/build/* && \
    cat << 'EOF' > /geant4lab/proyecto_lluvias_cosmicas/build/vis.mac
/vis/open OGL 600x600-0+0
/vis/viewer/set/autoRefresh true
/vis/verbose errors
/vis/drawVolume
/vis/viewer/set/viewpointVector -1 1 1
/vis/viewer/set/style wireframe
/vis/scene/add/trajectories smooth
/vis/scene/endOfEventAction accumulate
/run/initialize
/run/beamOn 1
/vis/viewer/flush
EOF

RUN cd /geant4lab/proyecto_lluvias_cosmicas/build && \
    /bin/bash -c "source /usr/local/bin/geant4make.sh && cmake .. && make -j$(nproc)"

WORKDIR /geant4lab/proyecto_lluvias_cosmicas/build

CMD ["/bin/bash"]
