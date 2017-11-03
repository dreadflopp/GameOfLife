/**
 * @file SupportStructures.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date October 2017
 * @version 0.1
 */

#ifndef GAMEOFLIFE_SUPPORTSTRUCTURES_H
#define GAMEOFLIFE_SUPPORTSTRUCTURES_H

/**
 * @struct Point
 * @brief Constitues a single Point in the simulated world.
 * @details The Point structure handles x and y (column/row) coordinates in the world
 * of Game of life, and is used to map Cell objects to their positions.
 * @test that the overloading of operator < works. Point A < Point B is true if point A.x is < B.x OR
 * if Point A.x == Point B.x && Point A.y < Point B.y
 */
struct Point {
    int x, y;

    // Overloading operator < for comparing Point objects
    bool operator < (const Point& other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }

    // Overloading operator == for comparing Point objects
    bool operator==(const Point& other) const {
        return x==other.x && y==other.y;
    }
};

/**
 * @struct Dimensions
 * @brief Data structure holding information about world dimensions in pixels.
 */
struct Dimensions {
    int WIDTH, HEIGHT;
};

#endif //GAMEOFLIFE_SUPPORTSTRUCTURES_H
