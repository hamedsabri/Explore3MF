## Explore3MF

Code repository of Youtube tutorial videos on using 3D Manufacturing Format (3MF) + Lib3MF library.

## Screenshot

![screenshot](https://user-images.githubusercontent.com/283793/42958954-23fe9532-8b55-11e8-8f85-2120209c719a.png)

## Windows & Mac OS X Building

1) Clone this project
2) Generate Visual Studio solution or Xcode project:
    - cd into cloned project directory
    - make a directory called build/
    - cd into the build/
    - on windows run cmake .. -G "YOUR VISUAL STUDIO VERSION Win64"
    - on mac run cmake .. -G "Xcode" -DCMAKE_OSX_ARCHITECTURES=x86_64
    - if you want release build simply pass -DCMAKE_BUILD_TYPE=Release
