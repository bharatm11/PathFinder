#ifndef POSITION_HPP
#define POSITION_HPP
/**
 * @file Position.hpp
 * @author Bharat Mathur [bharatm11]
 * @date 26 March 2026
 * @brief struct to define 2D position on the battlefield grid
 */

 #include <functional>

struct Position
{
    int row = 0; // Row coordinate (y-axis)
    int col = 0; // Column coordinate (x-axis)

    /**
     * @brief Equality comparison
     * @param pos Position to compare
     * @return true if positions are equal
     */
    bool operator==(const Position &pos) const
    {
        return row == pos.row && col == pos.col;
    }

    /**
     * @brief Inequality comparison
     * @param pos Position to compare
     * @return true if positions are not equal
     */
    bool operator!=(const Position &pos) const
    {
        return !(*this == pos);
    }

    /**
     * @brief Hash function to support unordered containers
     */
    struct PositionHash
    {
        /**
         * @brief Hash function for Position
         * @param pos Position
         * @return Hash value
         */
        std::size_t operator()(const Position &pos) const
        {
            return std::hash<int>()(pos.row) ^ (std::hash<int>()(pos.col) << 1);
        }
    };
};

#endif // POSITION_HPP
