#include "JsonLoader.hpp"
#include <fstream>
#include <iostream>
#include <exception>
#include <cmath>

int JsonLoader::normalizeTileValue(double value)
{
    static const int supportedTileCodes[] = {
        static_cast<int>(CellType::Open),
        static_cast<int>(CellType::Start),
        static_cast<int>(CellType::Elevated),
        static_cast<int>(CellType::Target)};

    // Find the closest supported tile code to the input value
    int closestTileCode = supportedTileCodes[0];
    double smallestDistance = std::fabs(value - static_cast<double>(closestTileCode));
    for (int candidateTileCode : supportedTileCodes)
    {
        const double candidateDistance = std::fabs(value - static_cast<double>(candidateTileCode));
        if (candidateDistance < smallestDistance)
        {
            closestTileCode = candidateTileCode;
            smallestDistance = candidateDistance;
        }
    }
    return closestTileCode;
}

bool JsonLoader::loadMap(const std::string &filepath,
                         std::vector<int> &outData,
                         int &outWidth,
                         int &outHeight)
{
    try
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filepath);
        }

        json j;
        file >> j;
        file.close();

        // Extract map dimensions
        if (j.contains("width") && j.contains("height"))
        {
            outWidth = j["width"].get<int>();
            outHeight = j["height"].get<int>();
        }
        else
        {
            // Fallback for editor-exported format: derive dimensions from canvas and tile size.
            if (!j.contains("canvas") || !j.contains("tilesets") || j["tilesets"].empty())
            {
                throw std::runtime_error("Missing map dimensions: expected width/height or canvas+tilesets");
            }

            const auto &canvas = j["canvas"];
            const auto &tileset = j["tilesets"][0];
            if (!canvas.contains("width") || !canvas.contains("height") ||
                !tileset.contains("tilewidth") || !tileset.contains("tileheight"))
            {
                throw std::runtime_error("Missing canvas/tile size fields needed to infer dimensions");
            }

            const int canvasWidth = canvas["width"].get<int>();
            const int canvasHeight = canvas["height"].get<int>();
            const int tileWidth = tileset["tilewidth"].get<int>();
            const int tileHeight = tileset["tileheight"].get<int>();
            if (tileWidth <= 0 || tileHeight <= 0)
            {
                throw std::runtime_error("Invalid tile size while inferring dimensions");
            }

            outWidth = canvasWidth / tileWidth;
            outHeight = canvasHeight / tileHeight;
        }

        // Extract data from layers
        if (!j.contains("layers") || j["layers"].empty())
        {
            throw std::runtime_error("Missing 'layers' field in JSON");
        }

        const auto &layer = j["layers"][0];
        if (!layer.contains("data"))
        {
            throw std::runtime_error("Missing 'data' field in layer");
        }

        if (!layer["data"].is_array())
        {
            throw std::runtime_error("Layer 'data' must be an array");
        }

        outData.clear();
        outData.reserve(layer["data"].size());
        for (const auto &value : layer["data"])
        {
            if (!value.is_number())
            {
                throw std::runtime_error("Layer data contains a non-numeric tile value");
            }
            outData.push_back(normalizeTileValue(value.get<double>()));
        }

        // Verify data size
        if (static_cast<int>(outData.size()) != outWidth * outHeight)
        {
            throw std::runtime_error("Data size mismatch: expected " +
                                     std::to_string(outWidth * outHeight) +
                                     " but got " + std::to_string(outData.size()));
        }

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading map: " << e.what() << std::endl;
        return false;
    }
}

bool JsonLoader::saveMap(const std::string &filepath,
                         const std::vector<std::vector<CellType>> &grid)
{
    try
    {
        if (grid.empty())
        {
            throw std::runtime_error("Grid is empty");
        }

        int height = static_cast<int>(grid.size());
        int width = static_cast<int>(grid[0].size());

        // Build data array
        std::vector<int> data;
        for (const auto &row : grid)
        {
            for (const auto &cell : row)
            {
                data.push_back(static_cast<int>(cell));
            }
        }

        // Create JSON structure
        json j;
        j["width"] = width;
        j["height"] = height;
        j["layers"] = json::array();
        j["layers"][0]["data"] = data;

        // Write to file
        std::ofstream file(filepath);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file for writing: " + filepath);
        }

        file << j.dump(2) << std::endl;
        file.close();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving map: " << e.what() << std::endl;
        return false;
    }
}
