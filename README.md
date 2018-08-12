## Explore3MF

Code repository of Youtube tutorial videos on using 3D Manufacturing Format (3MF) + Lib3MF library.

## Screenshot

![screenshot](https://user-images.githubusercontent.com/283793/42958954-23fe9532-8b55-11e8-8f85-2120209c719a.png)

## Windows & Mac OS X Build

1) Clone this project
2) Generate Visual Studio solution or Xcode project:
    - cd into cloned project directory
    - make a directory called build/
    - cd into the build/
    - on windows run cmake .. -G "YOUR VISUAL STUDIO VERSION Win64"
    - on mac run cmake .. -G "Xcode" -DCMAKE_OSX_ARCHITECTURES=x86_64
    - if you want release build, simply pass -DCMAKE_BUILD_TYPE=Release

## Linux (Ubuntu) Build

1. Install all needed tools, libraries, and compilers.
    
    - sudo apt-get install cmake clang xorg-dev libx11-dev libglu1-mesa-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev uuid-dev

2. Generate UNIX Makefile:

    - cd into cloned project directory
    - make a directory called build/
    - cd into the build/
    - run cmake ..
    - if you want release build, simply pass -DCMAKE_BUILD_TYPE=Release
    - make -j4 ( pass -j flag if you want to use more processors for compiling )
    - cd bin/
    - ./ThreeMFApp
