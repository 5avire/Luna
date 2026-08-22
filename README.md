# LunaEngine
A game engine built while following TheCherno's Game Engine series, with additional experimentation and learning along the way.

---

## Platform Support
Currently tested on Linux. Other platforms may work but are untested.

## Requirements
- CMake 3.16 or newer
- A C++ compiler with C++17 support
- OpenGL-compatible graphics drivers

---

## Building
First, clone the repository recursively with:
```
git clone --recursive https://github.com/5avire/Luna.git
```

Navigate to the folder, then

### Automatic
Run the provided build script:

#### Linux
```sh
./build.sh
```

#### Windows
```bat
build.bat
```
##### You can also double click the .bat file via file manager.

### Manual (All Platforms)
Configure and build the project:

```sh
cmake -S . -B build && cmake --build build
```
The compiled binaries will be placed in the `bin/` directory.

---
## Note
I use AI as a learning aid to help explain concepts and summarize documentation, particularly when official documentation is lengthy. The code itself is written by me as part of the learning process rather than copied from AI-generated solutions.
