#include <iostream>
#include <algorithm>
#include "Map.hpp"
#include "PathFinder.hpp"

char cellToChar(CellType cell)
{
    switch (cell)
    {
    case CellType::Start:
        return 'S';
    case CellType::Target:
        return 'T';
    case CellType::Elevated:
        return '#';
    case CellType::Open:
    default:
        return '.';
    }

    std::cout << "Start: " << "S" << std::endl;
    std::cout << "Target: " << "T" << std::endl;
    std::cout << "Elevated: " << "#" << std::endl;
    std::cout << "Open: " << "." << std::endl;
    std::cout << "Traversed path: " << "*" << std::endl;
}

bool isTraversedCell(const Position &cell, const std::vector<Position> &path)
{
    return (std::find(path.begin(), path.end(), cell) != path.end());
}

void printMap(const Map &map, const std::vector<Position> &path = {})
{
    const char *kYellow = "\033[33m";
    const char *kReset = "\033[0m";

    for (int r = 0; r < map.numRows(); ++r)
    {
        for (int c = 0; c < map.numCols(); ++c)
        {
            const Position cell{r, c};
            if (!path.empty() && isTraversedCell(cell, path) 
            && (map.getCellType(cell) != CellType::Start) && (map.getCellType(cell) != CellType::Target))
            {
                std::cout << kYellow << '*' << kReset << ' ';
            }
            else
            {
                std::cout << cellToChar(map.getCellType(cell)) << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    // test map generation
    // Map map;
    // map.generateRandom(32, 32);
    // printMap(map);

    // test JSON loading

    Map jsonMap;
    const std::string jsonPath = "../samples/take_home_project.json";

    bool loaded = false;

    if (jsonMap.loadFromJson(jsonPath))
    {
        std::cout << "Successfully loaded map from: " << jsonPath << std::endl;
        loaded = true;
    }
    else
    {
        std::cerr << "Failed to load map from JSON." << std::endl;
        return 1;
    }

    printMap(jsonMap);

    const Position start = jsonMap.findStart();
    const Position target = jsonMap.findTarget();
    if (start.row < 0 || target.row < 0)
    {
        std::cerr << "Map missing start or target tile." << std::endl;
        return 1;
    }

    Pathfinder pathfinder;
    const PathResult result = pathfinder.findPath(jsonMap, start, target);
    if (!result.success)
    {
        std::cerr << "Pathfinding failed: " << result.errorMessage << std::endl;
        return 1;
    }

    std::cout << "Path found. Length: " << result.path.size() << std::endl;

    // Print the path coordinates 
    if (result.path.size() == 0)
    {
        std::cout << "(empty)";
    }
    else
    {
        for (size_t i = 0; i < result.path.size(); ++i)
        {
            const auto &p = result.path[i];
            std::cout << "(" << p.row << "," << p.col << ")";
            if (i + 1 < result.path.size())
            {
                std::cout << " -> ";
            }
        }
    }

    std::cout << "\n";

    std::cout << "Solved map (* = traversed path):" << std::endl;
    printMap(jsonMap, result.path);

    return 0;
}
