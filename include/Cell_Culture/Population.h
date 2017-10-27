/*
 * @file Population.h
 * @author Andreas Lind
 * @version 0.1
 * @date 2017-10-27
*/

#ifndef POPULATION_H
#define POPULATION_H

#include<map>
#include<string>
#include "Cell.h"
#include "Support/Globals.h"
#include "GoL_Rules/RuleOfExistence.h"
#include "GoL_Rules/RuleFactory.h"

using namespace std;

/**
 * @class Population
 * @brief Representation of the complete society of cell existance and interactions
 * @details The Population constitutes of all current, previous and future generations of cells, both living and dead
 * as well as those not yet born. By mapping all cells to their respective positions in the simulation world,
 * Population has the complete knowledge of each cell's whereabouts. Furthermore, the class is responsible for
 * determining which rules should be required from the RuleFactory, and store the pointer to these as members.
 * Population's main responsibility during execution is determining which rule to apply for each new generation
 * and updating the cells to their new states.
 */
class Population
{
private:
    int generation;
    map<Point, Cell> cells;
    RuleOfExistence* evenRuleOfExistence;
    RuleOfExistence* oddRuleOfExistence;

    void randomizeCellCulture();
    void buildCellCultureFromFile();

public:
    /**
     *  @brief Constructor that initializes empty Population object
     *  @details Initializes Population object with generation = 0 and evenRuleExistance and oddRuleExistance as nullptrs
     */
    Population() : generation(0), evenRuleOfExistence(nullptr), oddRuleOfExistence(nullptr) {}

    /**
    *   @brief Destructor för deallocating Population object
    *   @details Deallocates evenRuleExistance and oddRuleExistance if not set as nullptrs
    */
    ~Population();

    /**
     *  @brief Function to initialize Population object with cells and evenRuleName and oddRuleName
     *  @param evenRuleName represents rules to be applied to every even numbered generation of cells
     *  @param oddRuleName represents rules to be applied to every odd numbered generation of cells. If left empty,
     *  same rule as evenRuleName will be applied
     *  @test that if randomized, test that stored cells are a copy of randomized cell values
     *  @test that if read from file, test that stored cells are a copy of the cell structure in the file
     */
    void initiatePopulation(string evenRuleName, string oddRuleName = "");

    /**
     *  @brief Function updates cells next state and applies rules for next generation
     *  @return Nr of generations incremented by 1
     *  @test require generation to be incremented by 1
     */
    int calculateNewGeneration();

    /**
     *  @brief Returns reference to cell specified by position
     *  @param position Represents coordinates in map with cells
     *  @return Cell at specified position
     */
    Cell& getCellAtPosition(Point position) { return cells.at(position); }

    /**
     *  @brief Returns total number of cells in population
     *  @details Returns cells.size() which equals the number of height * width of simulation world
     *  @return cells.size() Represents size of Map of cells
     *  @test after Population object first has been created, require return value == 0
     */
    int getTotalCellPopulation() { return cells.size(); }

};

#endif