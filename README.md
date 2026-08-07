# Miniproyecto Geant4: Simulación de Lluvias de Partículas Atmosféricas

Este repositorio contiene el código fuente y el Dockerfile para construir y ejecutar una simulación de lluvias de partículas atmosféricas producidas por rayos cósmicos utilizando **Geant4 11.2.0**.

## 🚀 Enlace a la Imagen de Docker Hub

La imagen pública del proyecto está alojada en Docker Hub:

docker pull shinjianddy/geant4-lluvias-cosmicas:latest

💻 Instrucciones para Ejecutar la Imagen
1. Permitir acceso al servidor gráfico en la máquina host:

xhost +local:docker

2. Descargar y ejecutar el contenedor:

docker run -it --rm \
  --net=host \
  --env="DISPLAY" \
  --env="LIBGL_ALWAYS_SOFTWARE=1" \
  --device /dev/dri \
  -v $HOME/.Xauthority:/root/.Xauthority:rw \
  shinjianddy/geant4-lluvias-cosmicas:latest

3. Ejecutar la simulación:

Una vez dentro del contenedor, ejecute:

./sim

📂 Estructura del Proyecto

/geant4lab/proyecto_lluvias_cosmicas/
├── CMakeLists.txt
├── sim.cc
├── include/
│   ├── DetectorConstruction.hh
│   ├── PhysicsList.hh
│   ├── PrimaryGenerator.hh
│   └── SensitiveDetector.hh
└── src/
    ├── DetectorConstruction.cc
    ├── PhysicsList.cc
    ├── PrimaryGenerator.cc
    └── SensitiveDetector.cc
