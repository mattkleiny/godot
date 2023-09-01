FROM mcr.microsoft.com/devcontainers/cpp:1-debian-11

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
     build-essential \
     python3 \
     scons \
     pkg-config \
     libx11-dev \
     libxcursor-dev \
     libxinerama-dev \
     libgl1-mesa-dev \
     libglu-dev \
     libasound2-dev \
     libpulse-dev \
     libudev-dev \
     libxi-dev \
     libxrandr-dev
