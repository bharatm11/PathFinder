
#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <string>

bool Map::loadFromJson(const std::string &filepath)
{

}

bool Map::saveToJson(const std::string &filepath) const
{

}

void Map::generateRandom(int rows, int cols, float wallRatio)
{
}

CellType Map::getCell(Position p) const
{
}

bool Map::isWalkable(Position p) const
{

}

bool Map::isInBounds(Position p) const
{
  
}

std::vector<Position> Map::getNeighbors(Position p) const
{
}

Position Map::findStart() const
{
}

Position Map::findTarget() const
{
}

void Map::setCell(Position p, CellType type)
{
}