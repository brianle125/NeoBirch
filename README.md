# sdl-engine
A 2D ECS-based game engine constructed with C++ and SDL2. 

Expanded from Carl Birch's BirchEngine: 
https://www.youtube.com/watch?v=QQzAHcojEKg

## Features
- Entity collision
- Projectiles
- Keyboard control
### Extended features
- Controller support
- In-game audio
- Entity health

And other improvements like:
- Cleaner code/architecture
- Safer memory managment


## Build Instructions
### Prerequisites
* CMake
* Python >= 3.8

### Building
1. Install conan.
```bash
$ pip install conan
```
2. Navigate to BirchEngine/ and create a build directory
```bash
$ mkdir build
$ cd build
```
3. Build dependencies, create build environment and build.

    1. Download dependencies
    ```bash
    $ conan install .. -s build_type=Debug --build=missing --output-folder=build
    ```
    2. Configure cmake and run the build.
    ```bash
    $ cmake -G "Visual Studio 16 2019" -A x64 ..
    ```
    3. Open the generated .sln file or run build with
    ```bash
    $ cmake --build . --preset conan-debug
    ```
