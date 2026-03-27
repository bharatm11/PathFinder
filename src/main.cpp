#include <iostream>
#include "Map.hpp"

namespace
{
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
} // namespace

int main(int argc, char *argv[])
{
    Map map;
    map.generateRandom(32, 32);
    printMap(map);

    return 0;
}
