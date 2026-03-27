#include "Map.hpp"

// returrns 

bool Map::loadFromJson(const std::string &filepath)
{
    return true;
}

bool Map::saveToJson(const std::string &filepath) const
{
    return true;
}

void Map::generateRandom(int rows, int cols, float wallRatio)
{
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