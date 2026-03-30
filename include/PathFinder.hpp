#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
/**
 * @file PathFinder.hpp
 * @author Bharat Mathur [bharatm11]
 * @date 29 March 2026
 * @brief implements the A* algorithm to find the shortest path from a start position to a target position on the map.
 */

#include <Position.hpp>
#include <Map.hpp>
#include <PathResult.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

class Pathfinder
{
public:
    /**
     * @brief Construct a Pathfinder instance
     */
    Pathfinder() = default;

    /**
     * @brief Find a path using A* algorithm
     * @param map The battlefield map
     * @param start Starting position
     * @param target Target position
     * @return PathResult containing the path or error message
     */
    PathResult findPath(const Map &map, Position start, Position target);

private:
    /**
     * @brief Node structure for A* algorithm
     */
    struct Node
    {
        Position m_pos;
        float m_gCost = 0.0f;         // Cost from start
        float m_hCost = 0.0f;         // Heuristic cost to goal (manhattan distance)
        Position m_parent = {-1, -1}; // Parent position in path

        /**
         * @brief Calculate f-cost (g + h)
         * @return f-cost value
         */
        float fCost() const { return m_gCost + m_hCost; }
    };

    /**
     * @brief Comparison functor for priority queue (min-heap by f-cost)
     */
    struct CompareNode
    {
        bool operator()(const Node &a, const Node &b) const
        {
            return a.fCost() > b.fCost();
        }
    };

    /**
     * @brief Calculate Manhattan distance heuristic
     * @param a First position
     * @param b Second position
     * @return Manhattan distance
     */
    float heuristic(Position a, Position b) const;

    /**
     * @brief Internal A* implementation
     * @param map The battlefield map
     * @param start Starting position
     * @param target Target position
     * @return PathResult
     */
    PathResult aStarSearch(
        const Map &map,
        Position start,
        Position target);

    /**
     * @brief Reconstruct path from parent pointers
     * @param parentMap Map of positions to their parents
     * @param start Starting position
     * @param target Ending position
     * @return Vector representing the path
     */
    std::vector<Position> reconstructPath(
        const std::unordered_map<Position, Position, Position::PositionHash> &parentMap,
        Position start,
        Position target) const;
};

#endif // PATHFINDER_HPP
