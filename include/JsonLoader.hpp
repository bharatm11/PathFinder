#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

/**
 * @file JsonLoader.hpp
 * @author Bharat Mathur [bharatm11]
 * @date 27 March 2026
 * @brief JSON loader for RiskyLab Tilemap format
 * Handles loading and saving maps in RiskyLab Tilemap JSON format.
 * Uses nlohmann/json library for JSON parsing.
 */

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "CellType.hpp"
#include "Position.hpp"

using json = nlohmann::json;

class JsonLoader
{
public:
     /**
      * @brief Class constructor
      */
     JsonLoader() = default;

     /**
      * @brief Load a RiskyLab Tilemap JSON file
      * @param filepath Path to the JSON file
      * @param outData Output vector of cell values (row-major order)
      * @param outWidth Output width (columns)
      * @param outHeight Output height (rows)
      * @return true if loading succeeded
      */
     static bool loadMap(const std::string &filepath,
                         std::vector<int> &outData,
                         int &outWidth,
                         int &outHeight);

     /**
      * @brief Save a map to RiskyLab Tilemap JSON format
      * @param filepath Path to output JSON file
      * @param grid 2D grid of cell types
      * @return true if saving succeeded
      */
     static bool saveMap(const std::string &filepath,
                         const std::vector<std::vector<CellType>> &grid);

     /**
      * @brief Save path positions to JSON
      * @param filepath Path to output JSON file
      * @param path Path positions to save
      * @return true if saving succeeded
      */
     static bool savePath(const std::string &filepath,
                          const std::vector<Position> &path);

     /**
      * @brief Load path positions from JSON
      * @param filepath Path to input JSON file
      * @param outPath Output path positions
      * @return true if loading succeeded
      */
     static bool loadPath(const std::string &filepath,
                          std::vector<Position> &outPath);

private:
     /**
      * @brief Normalize a tile value to the nearest supported tile code
      * @param value Input tile value
      * @return Normalized tile value
      */
     static int normalizeTileValue(double value);
};

#endif // JSONLOADER_HPP
