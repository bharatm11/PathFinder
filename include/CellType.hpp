#ifndef CELLTYPE_HPP
#define CELLTYPE_HPP
/**
* @file CellType.hpp
* @author Bharat Mathur [bharatm11]
* @date 26 March 2026
* @brief Cell type enumeration for the RiskyLab Tilemap format
*/


enum class CellType : int
{
    Open = -1,    // Open/reachable terrain
    Start = 0,    // Start position
    Elevated = 3, // Ureachable elevated terrain
    Target = 8    // Target position
};

#endif // CELLTYPE_HPP
