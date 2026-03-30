#include <iostream>
#include "Map.hpp"
#include "PathFinder.hpp"
#include "Renderer.hpp"

int main(int argc, char *argv[])
{
    // test map generation
    // Map map;
    // map.generateRandom(32, 32);
    // printMap(map);

    // test JSON loading

    Map jsonMap;
    const std::string jsonPath = "../samples/take_home_project.json";

    bool loaded = false;

    if (jsonMap.loadFromJson(jsonPath))
    {
        std::cout << "Successfully loaded map from: " << jsonPath << std::endl;
        loaded = true;
    }
    else
    {
        std::cerr << "Failed to load map from JSON." << std::endl;
        return 1;
    }

    Renderer::printMap(jsonMap);

    const Position start = jsonMap.findStart();
    const Position target = jsonMap.findTarget();
    if (start.row < 0 || target.row < 0)
    {
        std::cerr << "Map missing start or target tile." << std::endl;
        return 1;
    }

    Pathfinder pathfinder;
    const PathResult result = pathfinder.findPath(jsonMap, start, target);
    if (!result.success)
    {
        std::cerr << "Pathfinding failed: " << result.errorMessage << std::endl;
        return 1;
    }

    std::cout << "Path found. Length: " << result.path.size() << std::endl;

    // Print the path coordinates 
    Renderer::printPath(result.path);

    std::cout << "\n";

    std::cout << "Solved map (* = traversed path):" << std::endl;
    Renderer::printMap(jsonMap, result.path);

    return 0;
}
