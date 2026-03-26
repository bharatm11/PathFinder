#ifndef POSITION_HPP
#define POSITION_HPP
/**
* @file Position.hpp
* @author Bharat Mathur [bharatm11]
* @date 26 March 2026
* @brief struct to define 2D position on the battlefield grid
 */

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
};


#endif // POSITION_HPP
