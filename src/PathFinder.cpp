#include "PathFinder.hpp"
#include <algorithm>

float Pathfinder::heuristic(Position a, Position b) const
{
    // Manhattan distance
    // Using  manhattan as only 4 directions are allowed; no diagonal movement
    return static_cast<float>(std::abs(a.row - b.row) + std::abs(a.col - b.col));
}

PathResult Pathfinder::findPath(const Map &map, Position start, Position target)
{
    return aStarSearch(map, start, target);
}

PathResult Pathfinder::aStarSearch(const Map &map, Position start, Position target)
{
    PathResult result;

    if (!map.isWalkable(start))
    {
        result.errorMessage = "Start position is not walkable";
        return result; // Early exit 
    }

    if (!map.isWalkable(target))
    {
        result.errorMessage = "Target position is not walkable";
        return result; // Early exit
    }

    if (start == target)
    {
        result.success = true;
        result.path.push_back(start);
        return result; // Early exit
    }

    std::priority_queue<Node, std::vector<Node>, CompareNode> openSet; // unexplored nodes
    std::unordered_map<Position, Node, Position::PositionHash> closedSet; // explored nodes
    std::unordered_map<Position, Node, Position::PositionHash> nodeMap; // nodes by position
    std::unordered_map<Position, Position, Position::PositionHash> parentMap; // parent pointers for path reconstruction

    Node startNode;
    startNode.m_pos = start;
    startNode.m_gCost = 0.0f;
    startNode.m_hCost = heuristic(start, target);
    startNode.m_parent = {-1, -1};

    openSet.push(startNode);
    nodeMap[start] = startNode;

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        // If target reached, reconstruct the path and return success
        if (current.m_pos == target)
        {
            result.success = true;
            result.path = reconstructPath(parentMap, start, target);
            return result;
        }

        // Skip if this node has already been explored with a lower f-cost
        if (closedSet.count(current.m_pos) > 0)
        {
            continue;
        }
            
        // Set current node as explored
        closedSet[current.m_pos] = current;

        // Explore neighbors of the current node
        for (const auto &neighbor : map.getNeighbors(current.m_pos))
        {
            // Skip if neighbor is already explored
            if (closedSet.count(neighbor) > 0)
            {
                continue;
            }

            // Calculate tentative g-cost to neighbor
            float tentativeGCost = current.m_gCost + 1.0f;

            // If neighbor is not in open set or if lower g-cost path is found
            if ((nodeMap.count(neighbor) == 0) || (tentativeGCost < nodeMap[neighbor].m_gCost))
            {
                parentMap[neighbor] = current.m_pos;

                // Update or add neighbor node in open set
                Node neighborNode;
                neighborNode.m_pos = neighbor;
                neighborNode.m_gCost = tentativeGCost;
                neighborNode.m_hCost = heuristic(neighbor, target);
                neighborNode.m_parent = current.m_pos;

                //
                nodeMap[neighbor] = neighborNode;
                openSet.push(neighborNode);
            }
        }
    }

    result.errorMessage = "No path found - target unreachable";
    return result;
}

std::vector<Position> Pathfinder::reconstructPath(
    const std::unordered_map<Position, Position, Position::PositionHash> &parentMap,
    Position start,
    Position target) const
{
    std::vector<Position> path;

    // Start from the goal and walk backwards through parent pointers.
    Position current = target;

    while (!(current == start))
    {
        // Record current node while traversing backward.
        path.push_back(current);

        // If parent is missing, reconstruction is incomplete; stop safely.
        auto it = parentMap.find(current);
        if (it == parentMap.end())
            break;

        // Move one step toward the start.
        current = it->second;
    }

    // Include start node, then reverse to get start -> target order.
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
