/*
 * file GameOfLife-Test.cpp
 * author Mattias Lindell
 * author Andreas Lind
 * date 29 october 2017
 * version 0.1
*/
#include <random>
#include <Support/SupportStructures.h>
#include "catch.hpp"
#include "memstat.hpp"

/*
 * Testing the struct Point
 */
SCENARIO ("Testing the overloading of operator < in the struct Point") {
    GIVEN("Two points") {
        std::default_random_engine generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int> random(1, 1000);
        int ax = random(generator);
        int ay = random(generator);
        int bx = random(generator);
        int by = random(generator);

        Point a = {ax, ay};
        Point b = {bx, by};

        WHEN("The x value of point a is less than the x value of point b") {
            if (ax < bx)
                THEN("point a should be less than point b") {
                    REQUIRE( a<b );
                }
        }
        WHEN("The x value of point a is more than the x value of point b") {
            if (ax > bx)
                THEN("point b should be less than point a") {
                    REQUIRE( b<a );
                }
        }
        WHEN("The x value of point a is equal to the x value of point b") {
            if (ax == bx)
                AND_WHEN("The y value of point a is less than the y value of point b") {
                    if (ay < by)
                        THEN("point a should be less than point b") {
                            REQUIRE( a<b );
                        }
                }
                AND_WHEN("The y value of point a is more than the y value of point b") {
                    if (ay > by)
                        THEN("point b should be less than point a") {
                            REQUIRE( b<a );
                    }
            }
        }
    }
}