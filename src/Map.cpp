#include <random>
#include <iostream>
#include "Map.hpp"

void Map::generateRandom(int rows, int cols, float wallRatio)
{
    // Return early if dimensions are invalid
    if (rows <= 0 || cols <= 0)
    {
        std::cerr << "Error: Map dimensions must be positive" << std::endl;
        return;
    }

    m_numRows = rows;
    m_numCols = cols;

    // Initialize grid with all open cells
    m_grid.assign(m_numRows, std::vector<CellType>(m_numCols, CellType::Open));

    // Randomly place walls based on the specified ratio using a Bernoulli distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution makeWall(wallRatio);

    for (auto &row : m_grid)
    {
        for (auto &cell : row)
        {
            if (makeWall(gen))
            {
                cell = CellType::Elevated;
            }
        }
    }

    // Place start at bottom-left corner
    m_grid[m_numRows - 1][0] = CellType::Start;
    // Place target at top-right corner
    m_grid[0][m_numCols - 1] = CellType::Target;
}

CellType Map::getCell(Position p) const
{
    CellType defaultCell = CellType::Open;
    return defaultCell;
}

bool Map::isWalkable(Position p) const
{
    return false;
}

bool Map::isInBounds(Position p) const
{
    return false;
}

std::vector<Position> Map::getNeighbors(Position p) const
{
    return {};
}

Position Map::findStart() const
{
    return {};
}

Position Map::findTarget() const
{
    return {};
}

void Map::setCell(Position p, CellType type)
{
}