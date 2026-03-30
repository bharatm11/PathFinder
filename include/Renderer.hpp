#ifndef RENDERER_HPP
#define RENDERER_HPP
/**
 * @file Renderer.hpp
 * @author Bharat Mathur [bharatm11]
 * @date 29 March 2026
 * @brief Console rendering helpers for map.
 */

#include <vector>
#include "Map.hpp"
#include "Position.hpp"

class Renderer
{
public:
    /**
     * @brief Print the map to console
     * @param map Map to print
     * @param path Path traversed
     */
    static void printMap(const Map &map, const std::vector<Position> &path = {});

    /**
     * @brief Print a cell positions as path coordinates
     * @param path Vector of positions representing the path
     */
    static void printPath(const std::vector<Position> &path);

private:
    /**
     * @brief Convert a cell type to a character
     * @param cell Cell type
     * @return Character representation of the cell type
     */
    static char cellToChar(CellType cell);

    /**
     * @brief Check if a cell is part of the traversed path
     * @param cell Position of the cell to check
     * @param path Vector of positions representing the path
     * @return true if the cell is in the path, false otherwise
     */
    static bool isTraversedCell(const Position &cell, const std::vector<Position> &path);
};

#endif // RENDERER_HPP
