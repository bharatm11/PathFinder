#include "Renderer.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

char Renderer::cellToChar(CellType cell)
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

bool Renderer::isTraversedCell(const Position &cell, const std::vector<Position> &path)
{
    return std::find(path.begin(), path.end(), cell) != path.end();
}

void Renderer::printMap(const Map &map, const std::vector<Position> &path)
{
    const char *kYellow = "\033[33m";
    const char *kReset = "\033[0m";

    const int rowWidth = static_cast<int>(std::to_string(map.numRows() - 1).size());

    // Column numbers
    std::cout << std::string(rowWidth + 1, ' ');
    for (int c = 0; c < map.numCols(); ++c)
    {
        std::cout << std::left << std::setw(2) << c;
    }
    std::cout << '\n';

    for (int r = 0; r < map.numRows(); ++r)
    {
        // Row number
        std::cout << std::right << std::setw(rowWidth) << r << ' ';
        for (int c = 0; c < map.numCols(); ++c)
        {
            const Position cell{r, c};
            if (!path.empty() && isTraversedCell(cell, path) &&
                map.getCellType(cell) != CellType::Start &&
                map.getCellType(cell) != CellType::Target)
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

void Renderer::printPath(const std::vector<Position> &path)
{
    if (path.empty())
    {
        std::cout << "(empty)";
        return;
    }

    for (size_t i = 0; i < path.size(); ++i)
    {
        const Position &p = path[i];
        std::cout << "(" << p.row << "," << p.col << ")";
        if (i + 1 < path.size())
        {
            std::cout << " -> ";
        }
    }
}
