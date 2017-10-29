/**
 * @file RuleOfExistence.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date October 2017
 * @version 0.1
*/
#ifndef RULEOFEXISTENCE_H
#define RULEOFEXISTENCE_H

#include<string>
#include<map>
#include<vector>
#include "Cell_Culture/Cell.h"
#include "Support/Globals.h"
using namespace std;

/*
These rules lies at the heart
of the simulation, and determines the fate of each cell in the world population.
*/

/**
 * @struct PopulationLimits
 * @brief Data structure for storing population limits
 * @details Data structure for storing population limits. Used by rules to determine what ACTION to make.
 */
struct PopulationLimits {
    int UNDERPOPULATION, // cell dies of loneliness
            OVERPOPULATION, // cell dies of over crowding
            RESURRECTION; // cell lives on / is resurrected
};

/**
 * @struct Directions
 * @brief Data structure for storing directional values.
 * @details Data structure for storing directional values. Used by rules to determine neighbouring cells.
 */
struct Directions {
    int HORIZONTAL, VERTICAL;
};

// All directions; N, E, S, W, NE, SE, SW, NW
const vector<Directions> ALL_DIRECTIONS{ { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 },{ 1,-1 },{ 1,1 },{ -1,1 },{ -1,-1 } };

// Cardinal directions; N, E, S, W
const vector<Directions> CARDINAL{ { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 } };

// Diagonal directions; NE, SE, SW, NW
const vector<Directions> DIAGONAL{ { 1,-1 },{ 1,1 },{ -1,1 },{ -1,-1 } };

/**
 * @class RuleOfExistence
 * @brief Abstract base class, upon which concrete rules will derive.
 * @details The derivations of RuleOfExistence is what determines the culture of Cell Population. Each rule implements
 * specific behaviours and so may execute some parts in different orders. In order to accommodate this
 * requirement RuleOfExistence will utilize a **Template Method** design pattern, where all derived rules
 * implements their logic based on the virtual method executeRule().
 */
class RuleOfExistence {
protected:
    string ruleName;

    // Reference to the population of cells
    map<Point, Cell>& cells;

    // Amounts of alive neighbouring cells, with specified limits
    const PopulationLimits POPULATION_LIMITS;

    // The directions, by which neighbouring cells are identified
    const vector<Directions>& DIRECTIONS;

    int countAliveNeighbours(Point currentPoint);
    ACTION getAction(int aliveNeighbours, bool isAlive);

public:
    /**
     * @brief Constructor. The data members are not initiated since this is a class from which
     * actual rules will derive.
     * @param limits sets limits for the population
     * @param cells the entire population, passed by reference
     * @param DIRECTIONS sets the valid directions in the simulation
     * @param ruleName sets the name of the rule
     */
    RuleOfExistence(PopulationLimits limits, map<Point, Cell>& cells, const vector<Directions>& DIRECTIONS, string ruleName)
            : POPULATION_LIMITS(limits), cells(cells), DIRECTIONS(DIRECTIONS), ruleName(ruleName) {}
    virtual ~RuleOfExistence() {}

    // Execute rule, in order specific to the concrete rule, by utilizing template method DP
    /**
     * @brief virtual function without implementation
     * @details this function will be overrided in the derived clases
     */
    virtual void executeRule() = 0;

    /**
     * @brief Check what the name of a rule is
     * @return the name of the rule
     */
    string getRuleName() { return ruleName; }
};

#endif