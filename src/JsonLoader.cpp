#include "JsonLoader.hpp"
#include <fstream>
#include <iostream>
#include <exception>

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

        // Extract width and height
        if (!j.contains("width") || !j.contains("height"))
        {
            throw std::runtime_error("Missing 'width' or 'height' field in JSON");
        }

        outWidth = j["width"].get<int>();
        outHeight = j["height"].get<int>();

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

        outData = layer["data"].get<std::vector<int>>();

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
