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

## Example Usage

The app runs as an interactive console menu.

### Example 1: Load a map and run pathfinding

1. Choose `1` (Load map from JSON)
2. Enter: `../samples/take_home_project.json`
3. Choose `5` (Run pathfinding)

Expected output includes:
- Path length
- Traversed path coordinates
- Solved map with `*` over the traversed path

### Example 2: Generate a random map and solve

1. Choose `2` (Generate random map)
2. Enter rows, cols, and wall ratio (e.g. `32`, `32`, `0.2`)
3. Choose `5` (Run pathfinding)

### Example 3: Override start/target then solve

1. Load or generate a map first
2. Choose `3` and enter new start `row` and `col`
3. Choose `4` and enter new target `row` and `col`
4. Choose `5` to run pathfinding

### Example 4: Save current map

1. Load/generate/edit map state
2. Choose `7` (Save map to JSON)
3. Enter output path, for example: `../samples/random_map.json`

## Generate Docs (Doxygen)

```
cd build
cmake .. -DDOXYGEN_EXECUTABLE="C:/Program Files/doxygen/bin/doxygen.exe"
cmake --build . --target docs
```

Open: `docs/html/index.html`

## Known Bugs

- JSON normalization + marker ambiguity:
	When importing JSON, numeric tile values are normalized to the nearest supported cell type. If input data contains noisy/non-standard values, this can produce unexpected `Start` or `Target` cells.

- Multiple start/target markers on import:
	If a JSON map contains multiple `Start` (`0`) or `Target` (`8`) cells, the loader currently keeps all of them in the grid, and pathfinding uses the first one found during scan (`findStart`/`findTarget`). This may lead to multiple start or target locations.
