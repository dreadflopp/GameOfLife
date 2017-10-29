/**
 * @file RuleOfExistance_Erik.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date 2017-10-29
 * @version 0.1
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
#define GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H

#include "RuleOfExistence.h"

/**
 * @class RuleOfExistence_Erik
 * @brief Erik's RuleOfExistence, derived class of RuleOfExistance. Based on Conway's rule while also differentiate the
 * appearance of cells based on their age.
 * @details Concrete Rule of existence, implementing Erik's rule.
 * Sentient lifeforms is rarely created, but once in a while a cell has lived enough generations to become as wise as Erik.

 *- Once a cell has survived a minimum amount of generations it will recieve a color to distinguish itself from younger ones.
 *- If such a cell would then survive another set amount of generations, it will be marked with a value of **E**.
 *- In the extreme case, where the cell has achieved above requirements and is determined to be the oldest living cell, it will
 *  become a **prime elder**, and have its color changed once again. A generation may only have one such elder.
 */
class RuleOfExistence_Erik : public RuleOfExistence
{
private:
    char usedCellValue;	// char value to differentiate very old cells.
    Cell* primeElder;

    void erikfyCell(Cell& cell, ACTION action);
    void setPrimeElder(Cell* newElder);

public:
    /**
     * @brief constructor, derived from base class RuleOfExistance
     * @details apart from initiating all common data members from base class, data member usedCellValue is initiated
     * with char value 'E' to signify an old cell, and primeElder to nullPtr
     * @param cells represents the entire population, passed by reference
     */
    RuleOfExistence_Erik(map<Point, Cell>& cells)
            : RuleOfExistence({2,3,3}, cells, ALL_DIRECTIONS, "erik"), usedCellValue('E') {
        primeElder = nullptr;
    }
    ~RuleOfExistence_Erik() {}

    /**
     * @brief Execute the rule specific for Erik
     * @test that cells older than 5 generations recieves an old age color
     * @test that if the cell is older than 10 generations, it also gets the value 'E'
     * @test that the cell that have lived the longest and minimum 10 generations recieves an elder age color
     * @test that if an old cell(older than 5 generations) dies, its value is reset from 'E' to '#'
     */
    void executeRule();
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
