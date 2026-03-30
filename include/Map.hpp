#ifndef MAP_HPP
#define MAP_HPP
/**
* @file Map.hpp
* @author Bharat Mathur [bharatm11]
* @date 26 March 2026
* @brief Manages the grid and map operations. Handles loading/saving maps in JSON format,
* storing the grid, and querying cell information.
*/

#include <vector>
#include <string>
#include "Position.hpp"
#include "CellType.hpp"

class Map
{
public:
    /**
     * @brief Construct an empty map
     * param none
     * return none
     */
    Map() = default;

    /**
     * @brief Load a map from a RiskyLab Tilemap JSON file
     * @param filepath Path to the JSON file
     * @return true if load succeeded, false otherwise
     */
    bool loadFromJson(const std::string &filepath);

    /**
     * @brief Save map to a RiskyLab Tilemap JSON file
     * @param filepath Path to the output JSON file
     * @return true if save succeeded, false otherwise
     */
    bool saveToJson(const std::string &filepath) const;

    /**
     * @brief Generate a random map
     * @param rows Number of rows in the map
     * @param cols Number of columns in the map
     * @param wallRatio Ratio of walls to total cells (default 0.2f = 20%)
     */
    void generateRandom(int rows, int cols, float wallRatio = 0.2f);

    /**
     * @brief Get the cell type at a position
     * @param p Position to query
     * @return Cell type at the position, or Open if out of bounds
     */
    CellType getCellType(Position p) const;

    /**
     * @brief Check if a position is walkable
     * @param p Position to check
     * @return true if position is walkable (not Elevated and in bounds)
     */
    bool isWalkable(Position p) const;

    /**
     * @brief Check if a position is within map bounds
     * @param p Position to check
     * @return true if position is within bounds
     */
    bool isInBounds(Position p) const;

    /**
     * @brief Get number of rows
     * @return Number of rows
     */
    int numRows() const { return m_numRows; }

    /**
     * @brief Get number of columns
     * @return Number of columns
     */
    int numCols() const { return m_numCols; }

    /**
     * @brief Get all walkable cells from a position (4-directions)
     * @param p Position
     * @return Vector of walkable neighbor positions
     */
    std::vector<Position> getNeighbors(Position p) const;

    /**
     * @brief Find the start position in the map
     * @return Start position (cell value == 0), or {-1, -1} if not found
     */
    Position findStart() const;

    /**
     * @brief Find the target position in the map
     * @return Target position (cell value == 8), or {-1, -1} if not found
     */
    Position findTarget() const;

    /**
     * @brief Set a cell to a specific type
     * @param p Position to set
     * @param type Cell type to set
     */
    void setCell(Position p, CellType type);

    std::vector<std::vector<CellType>> m_grid; // 2D map grid 
    int m_numRows = 0;                            // Number of rows
    int m_numCols = 0;                            // Number of columns
};

#endif // MAP_HPP