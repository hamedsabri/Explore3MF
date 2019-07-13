## Explore3MF

Code repository of Youtube tutorial videos on using 3D Manufacturing Format (3MF) + Lib3MF library.

## Status
|  Build Status |
|-------------- |
|![Win-x64](doc/images/win.png) **Windows x64** ![macOS-x64](doc/images/apple.png) **macOS** ![Linux-x64](doc/images/ubuntu.png) **Linux x64** |
| [![Build Status](https://dev.azure.com/homemadecode3d/homemadecode3d/_apis/build/status/Explore3D-PipeLine?branchName=azure)](https://dev.azure.com/homemadecode3d/homemadecode3d/_build/latest?definitionId=9&branchName=azure)|

## Screenshot

![screenshot](https://user-images.githubusercontent.com/283793/42958954-23fe9532-8b55-11e8-8f85-2120209c719a.png)

## Building With python script

The simplest way to build the project is by running the ```build.py``` script.
```
usage: build.py [-h] [--generator GENERATOR] [--build_dir BUILD_DIR]
                [--build-debug] [--build-release] [--build-relwithdebug]
                [--build-args [BUILD_ARGS [BUILD_ARGS ...]]] [-j JOBS]
                [--force FORCE_CLEAN_BUILD]
                install_dir
```
###### 1. Install prerequisites

- Required:
  - C++ compiler:
       - Gcc
       - Xcode
       - Microsoft Visual Studio
  - CMake 
  - Python
- Optional
  - Ninja

###### 2. Build location
By default the build directory is created in the install_dir but the location can change to where ever you want by setting the ```--build_dir``` flag.

###### 3. Build Log
Build log ```log.txt``` is generated inside the build directory.

###### 4. CMake Generator
It is up to the user to select the Cmake Generator of choice.To use the Ninja Generator, you need to first install the Ninja binary from https://ninja-build.org/ You then need to set the ```generator``` flag to Ninja and the ```CMAKE_MAKE_PROGRAM variable``` to the Ninja binary you downloaded.

## Building With CMake on Windows & Mac OS X 

1) Clone this project
2) Generate Visual Studio solution or Xcode project:
    - cd into cloned project directory
    - make a directory called build/
    - cd into the build/
    - on windows run cmake .. -G "YOUR VISUAL STUDIO VERSION Win64"
    - on mac run cmake .. -G "Xcode" -DCMAKE_OSX_ARCHITECTURES=x86_64
    - if you want release build, simply pass -DCMAKE_BUILD_TYPE=Release

## Building With CMake on RedHat & Debian 

1. Install all needed tools, libraries, and compilers.

#### Debian    
    sudo apt-get install cmake clang xorg-dev libx11-dev libglu1-mesa-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx  libgl1-mesa-dev uuid-dev gtk+3.0

#### RedHat
    sudo dnf -y install cmake clang libX11-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel mesa-libGL gtk3-devel uuid-devel

2. Generate UNIX Makefile:

    - cd into cloned project directory
    - make a directory called build/
    - cd into the build/
    - run cmake ..
    - if you want release build, simply pass -DCMAKE_BUILD_TYPE=Release
    - make -j4 ( pass -j flag if you want to use more processors for compiling )
    - cd bin/
    - ./ThreeMFApp
