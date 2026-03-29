#include <iostream>
#include "Map.hpp"

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
}

void printMap(const Map &map)
{
    for (int r = 0; r < map.numRows(); ++r)
    {
        for (int c = 0; c < map.numCols(); ++c)
        {
            std::cout << cellToChar(map.getCellType({r, c})) << ' ';
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

    return 0;
}
