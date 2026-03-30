#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Map.hpp"
#include "PathFinder.hpp"
#include "Renderer.hpp"

namespace ConsoleApp
{
    template <typename T>

    /**
     *  @brief Read a number from console
     *  @param prompt Prompt message
     *  @param outValue Variable to store the parsed number
     *  @return true if parsing success
     */
    bool readNumber(const std::string &prompt, T &outValue)
    {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line))
        {
            return false;
        }

        std::istringstream iss(line);
        return (iss >> outValue) && iss.eof();
    }

    /** @brief Read a position (row and column) from console. Calls readNumber for each coordinate.
     * @return Position struct with the parsed coordinates, or {-1, -1} on failure
     */
    Position getPositionFromInput()
    {
        int row = -1;
        int col = -1;

        if (!readNumber("Enter row: ", row) || !readNumber("Enter col: ", col))
        {
            return {-1, -1}; // Return invalid position on failure
        }

        return {row, col};
    }

    /**
     *  @brief Display main menu
     */
    void displayMainMenu()
    {
        std::cout
            << "\n=== RTS Pathfinder ===\n"
            << "1. Load map from JSON\n"
            << "2. Generate random map\n"
            << "3. Set start position\n"
            << "4. Set target position\n"
            << "5. Run pathfinding\n"
            << "6. Show current map\n"
            << "7. Save map to JSON\n"
            << "8. Save last path positions\n"
            << "9. Read path positions from file\n"
            << "10. Exit\n"
            << "Select option: ";
    }

    /**
     *  @brief Replace existing marker (start or target) on the map with a new position.
     *  @param map Map to modify
     *  @param marker CellType::Start or CellType::Target to replace
     *  @param newPosition New position for the marker
     */
    void replaceMarker(Map &map, CellType marker, Position newPosition)
     {
         for (int r = 0; r < map.numRows(); ++r)
         {
             for (int c = 0; c < map.numCols(); ++c)
             {
                 const Position cell{r, c};
                 if (map.getCellType(cell) == marker)
                 {
                     map.setCell(cell, CellType::Open);
                 }
             }
         }

         map.setCell(newPosition, marker);
     }

     /**
      *  @brief Execute pathfinder
      *  @param map Map to traverse
      *  @param start Start position
      *  @param target Target position
      */
     bool executePathfinding(Map &map, Position start, Position target, std::vector<Position> &outPath)
     {
         if (start.row == -1 || target.row == -1)
         {
             std::cerr << "Error: Start or target not set." << std::endl;
             return false;
         }

         if (!map.isInBounds(start) || !map.isInBounds(target))
         {
             std::cerr << "Error: Start or target out of bounds." << std::endl;
             return false;
         }

         std::cout << "Running pathfinding from (" << start.row << "," << start.col
                   << ") to (" << target.row << "," << target.col << ")..." << std::endl;

         Pathfinder pathfinder;
         const PathResult result = pathfinder.findPath(map, start, target);

         if (!result.success)
         {
             std::cerr << "Pathfinding failed: " << result.errorMessage << std::endl;
             return false;
         }

         std::cout << "Path found. Length: " << result.path.size() << std::endl;
         Renderer::printPath(result.path);
         std::cout << '\n';

         std::cout << "Solved map (* = traversed path):" << std::endl;
         Renderer::printMap(map, result.path);

         outPath = result.path;
         return true;
     }
} // namespace ConsoleApp

int main(int argc, char *argv[])
{
    Map map;
    Position start{-1, -1};
    Position target{-1, -1};
    std::vector<Position> lastPath;
    bool hasMap = false;
    bool running = true;

    while (running)
    {
        ConsoleApp::displayMainMenu();

        int choice = 0;
        if (!ConsoleApp::readNumber("", choice))
        {
            std::cerr << "Invalid input." << std::endl;
            continue;
        }

        switch (choice)
        {
        case 1: // Load map from JSON
        {
            std::cout << "Enter JSON file path: ";
            std::string filepath;
            std::getline(std::cin, filepath);

            if (map.loadFromJson(filepath))
            {
                hasMap = true;
                start = map.findStart();
                target = map.findTarget();
                std::cout << "Map loaded successfully (" << map.numRows() << "x" << map.numCols() << ")" << std::endl;

                if (start.row != -1)
                {
                    std::cout << "Start position: (" << start.row << "," << start.col << ")" << std::endl;
                }
                if (target.row != -1)
                {
                    std::cout << "Target position: (" << target.row << "," << target.col << ")" << std::endl;
                }
            }
            else
            {
                std::cerr << "Failed to load map from JSON." << std::endl;
            }
            break;
        }

        case 2: // Generate random map
        {
            int rows = 0;
            int cols = 0;
            float wallRatio = 0.2f;

            if (!ConsoleApp::readNumber("Enter number of rows: ", rows) || !ConsoleApp::readNumber("Enter number of cols: ", cols))
            {
                std::cerr << "Error: Invalid dimensions." << std::endl;
                break;
            }

            if (!ConsoleApp::readNumber("Enter wall ratio (0.0-1.0, default 0.2): ", wallRatio) || wallRatio < 0.0f || wallRatio > 1.0f)
            {
                wallRatio = 0.2f;
            }

            map.generateRandom(rows, cols, wallRatio);
            hasMap = true;
            start = map.findStart();
            target = map.findTarget();
            std::cout << "Random map generated (" << rows << "x" << cols << ")" << std::endl;
            break;
        }

        case 3: // Set start position (overrides existing start)
        {
            if (!hasMap)
            {
                std::cerr << "Error: No map loaded." << std::endl;
                break;
            }

            std::cout << "Set start position:" << std::endl;
            const Position newStart = ConsoleApp::getPositionFromInput();
            if (!map.isWalkable(newStart))
            {
                std::cerr << "Error: Position is not walkable. Start not set." << std::endl;
                break;
            }

            start = newStart;
            ConsoleApp::replaceMarker(map, CellType::Start, start);
            if (target == start)
            {
                target = {-1, -1};
                std::cout << "Start now overlaps old target; please set a new target." << std::endl;
            }
            std::cout << "Start position set to (" << start.row << "," << start.col << ")" << std::endl;
            break;
        }

        case 4: // Set target position (overrides existing target)
        {
            if (!hasMap)
            {
                std::cerr << "Error: No map loaded." << std::endl;
                break;
            }

            std::cout << "Set target position:" << std::endl;
            const Position newTarget = ConsoleApp::getPositionFromInput();
            if (!map.isWalkable(newTarget))
            {
                std::cerr << "Error: Position is not walkable. Target not set." << std::endl;
                break;
            }

            target = newTarget;
            ConsoleApp::replaceMarker(map, CellType::Target, target);
            if (start == target)
            {
                start = {-1, -1};
                std::cout << "Target now overlaps old start; please set a new start." << std::endl;
            }
            std::cout << "Target position set to (" << target.row << "," << target.col << ")" << std::endl;
            break;
        }

        case 5: // Run pathfinding
        {
            if (!hasMap)
            {
                std::cerr << "Error: No map loaded." << std::endl;
                break;
            }

            if (ConsoleApp::executePathfinding(map, start, target, lastPath))
            {
                std::cout << "Stored " << lastPath.size() << " result positions in memory." << std::endl;
            }
            break;
        }

        case 6: // Print map
        {
            if (!hasMap)
            {
                std::cerr << "Error: No map loaded." << std::endl;
                break;
            }
            Renderer::printMap(map);
            break;
        }

        case 7: // Save map
        {
            if (!hasMap)
            {
                std::cerr << "Error: No map loaded." << std::endl;
                break;
            }

            std::cout << "Enter output JSON file path: ";
            std::string outputPath;
            std::getline(std::cin, outputPath);

            if (map.saveToJson(outputPath))
            {
                std::cout << "Map saved to: " << outputPath << std::endl;
            }
            else
            {
                std::cerr << "Failed to save map." << std::endl;
            }
            break;
        }

        case 8: // Save last path positions
        {
            if (lastPath.empty())
            {
                std::cerr << "Error: No path results available. Run pathfinding first." << std::endl;
                break;
            }

            std::cout << "Enter output path JSON file: ";
            std::string outputPath;
            std::getline(std::cin, outputPath);

            if (map.savePathToJson(outputPath, lastPath))
            {
                std::cout << "Path positions saved to: " << outputPath << std::endl;
            }
            else
            {
                std::cerr << "Failed to save path positions." << std::endl;
            }
            break;
        }

        case 9: // Read path positions
        {
            std::cout << "Enter input path JSON file: ";
            std::string inputPath;
            std::getline(std::cin, inputPath);

            std::vector<Position> loadedPath;
            if (map.loadPathFromJson(inputPath, loadedPath))
            {
                lastPath = loadedPath;
                std::cout << "Read " << lastPath.size() << " path positions:" << std::endl;
                Renderer::printPath(lastPath);
                std::cout << '\n';

                if (hasMap)
                {
                    std::cout << "Rendered path on current map (* = traversed path):" << std::endl;
                    Renderer::printMap(map, lastPath);
                }
                else
                {
                    std::cout << "Map not loaded, so only path coordinates were displayed." << std::endl;
                }
            }
            else
            {
                std::cerr << "Failed to read path positions." << std::endl;
            }
            break;
        }

        case 10: // Exit
            std::cout << "Exiting..." << std::endl;
            running = false;
            break;

        default:
            std::cerr << "Invalid option." << std::endl;
            break;
        }
    }

    return 0;
}
