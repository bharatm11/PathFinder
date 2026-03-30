#ifndef PATHRESULT_HPP
#define PATHRESULT_HPP
/**
 * @file PathResult.hpp
 * @author Bharat Mathur [bharatm11]
 * @date 29 March 2026
 * @brief Result struct returned PathFinder A* search
 */

#include <vector>
#include <string>
#include "Position.hpp"

struct PathResult
{
    bool success = false; // If a path was successfully found or not
    std::vector<Position> path; // Vector of positions representing the path from start to target 
    std::string errorMessage; // Error message describing the failure reason. Empty if success.
};

#endif // PATHRESULT_HPP
