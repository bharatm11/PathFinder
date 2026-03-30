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
    bool success = false;
    std::vector<Position> path;
    std::string errorMessage;
};

#endif // PATHRESULT_HPP
