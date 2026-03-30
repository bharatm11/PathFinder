# RTS Pathfinder

A* pathfinding demo on a grid map loaded from JSON.

## Dependencies

- CMake 3.16+
- C++17 compiler (Visual Studio 2022 Build Tools on Windows)
- nlohmann/json (auto-fetched from github by CMake)
- Doxygen (optional, for docs)

## Install Doxygen (Windows)

- Download from https://www.doxygen.nl/download.html
- Install to default location (`C:\Program Files\doxygen\bin`)

Verify:

```
doxygen --version
```

If `doxygen` is not recognized, add this folder to PATH:

```
C:\Program Files\doxygen\bin
```

## Build

```
cd build
cmake ..
cmake --build .
```

## Run

```
cd build
.\Debug\RTS_Pathfinder.exe
```

## Generate Docs (Doxygen)

```
cd build
cmake .. -DDOXYGEN_EXECUTABLE="C:/Program Files/doxygen/bin/doxygen.exe"
cmake --build . --target docs
```

Open: `build/docs/html/index.html`
