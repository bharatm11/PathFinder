# RTS Pathfinder

A* pathfinding demo on a grid map loaded from JSON.

## Dependencies

- CMake 3.16+
- C++17 compiler (Visual Studio 2022 Build Tools on Windows)
- nlohmann/json (auto-fetched from github by CMake)
- Doxygen (optional, for docs)
- Graphviz (optional, required for UML/call graphs in docs)

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

## Install Graphviz (Windows, for UML)

- Download from https://graphviz.org/download/
- Install Graphviz (default location is usually `C:\Program Files\Graphviz\bin`)
- Ensure `dot` is available on PATH

Verify:

```
dot -V
```

If `dot` is not recognized, add this folder to PATH:

```
C:\Program Files\Graphviz\bin
```

After installing Graphviz, regenerate docs so UML/call graphs are included:

```
cd build
cmake ..
cmake --build . --target docs
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

## Overview of Project Structure

- `include/CellType.hpp`
	- Defines the `CellType` enum used to label map cells (start, target, wall, free, path).
- `include/Position.hpp`
	- Defines the `Position` coordinate type and hash support used by pathfinding containers.
- `include/PathResult.hpp`
	- Defines `PathResult`, the result object returned by the solver (`success`, `path`, `errorMessage`).
- `include/Map.hpp` and `src/Map.cpp`
	- Defines `Map`, the grid data model with map generation, cell access, start/target lookup, and JSON load/save integration.
- `include/JsonLoader.hpp` and `src/JsonLoader.cpp`
	- Defines `JsonLoader`, the serialization layer for reading/writing map JSON and normalizing incoming tile values.
- `include/PathFinder.hpp` and `src/PathFinder.cpp`
	- Defines `PathFinder`, the A* search engine for single-unit shortest-path computation on the grid.
- `include/Renderer.hpp` and `src/Renderer.cpp`
	- Defines `Renderer`, responsible for console output of maps and solved paths.
- `src/main.cpp`
	- Implements the interactive CLI workflow: load/generate map, set start/target, run pathfinding, render, and save.

## Design Decisions

1. Why A* for pathfinding
	- A* fits this project's discrete 2D grid and gives deterministic, optimal shortest paths when used with an admissible heuristic.
	- Compared with Dijkstra, A* typically explores fewer nodes by using goal-directed search, so it is faster in practice on most maps.
	- Compared with RRT, A* is a better match for fixed-cost grid navigation because RRT is sampling-based, more suited to continuous/high-dimensional spaces, and does not naturally guarantee shortest paths.

2. Manhattan distance heuristic
	- The grid uses 4-direction movement (up, down, left, right), so Manhattan distance directly matches movement cost on this topology.
	- We use:
	  - `h(n) = |row_n - row_goal| + |col_n - col_goal|`
	- This heuristic is admissible and consistent for 4-neighbor grids, which preserves A* optimality and reduces unnecessary search.

## Known Bugs

- JSON normalization + marker ambiguity:
	When importing JSON, numeric tile values are normalized to the nearest supported cell type. If input data contains noisy/non-standard values, this can produce unexpected `Start` or `Target` cells.

- Multiple start/target markers on import:
	If a JSON map contains multiple `Start` (`0`) or `Target` (`8`) cells, the loader currently keeps all of them in the grid, and pathfinding uses the first one found during scan (`findStart`/`findTarget`). This may lead to multiple start or target locations.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.