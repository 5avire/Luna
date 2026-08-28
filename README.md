# Luna [![License](https://img.shields.io/github/license/5avire/Luna.svg)](https://github.com/5avire/Luna/blob/main/LICENSE)

<div align="center">

![Luna Logo](./Resources/Images/LunaLogo.png)

</div>

A game engine built while following TheCherno's Game Engine series, with additional experimentation and learning along the way.
Currently focuses primarily on 2D rendering.

---

## Platform Support

- Linux — tested
- Other platform may/may not work.

## Requirements
- CMake 3.16 or newer
- A C++ compiler with C++17 support
- OpenGL-compatible graphics drivers

---

## Configuring for compiling:
First, clone the repository recursively with:
```
git clone --recursive https://github.com/5avire/Luna.git
```

Navigate to the folder, then

### Automatic
Run the provided build script via terminal / command prompt from project root:

#### Linux
```sh
./scripts/Linux-Generate.sh
```

#### Windows
```bat
scripts\Win-Generate.bat
```
You can also double click on windows to launch it.

### Manual (All Platforms)
Configure and build the project:

```sh
cmake -S . -B build
```

---
## Note
This is a learning experience from the tutorial until a certain point from where I will diverge off and start adding more things.

## Plans after the series ends
* Implement proper 3D rendering as series focuses on Renderer 2D.
* Learn and implement Vulkan backend.
