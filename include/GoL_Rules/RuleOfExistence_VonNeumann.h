/**
 * @file RuleOfExistence_VonNeumann.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date 2017-10-29
 * @version 0.1
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
#define GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H

#include "RuleOfExistence.h"

/**
 * @class RuleOfExistence_VonNeumann
 * @brief Von Neumann's RuleOfExistence, differs from Conway in that only 4 neighbours are accounted for.
 * @details Concrete Rule of existence, implementing Von Neumann's rule.
 * Only difference from Conway is that neighbours are determined using only cardinal directions (N, E, S, W).
 */
class RuleOfExistence_VonNeumann : public RuleOfExistence
{
private:

public:
    RuleOfExistence_VonNeumann(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, CARDINAL, "von_neumann") {}
    ~RuleOfExistence_VonNeumann() {}

    /**
     * @brief Execute the rule specific for VonNeumann
     * @test that only cell neighbours in CARDINAL directions are counted
     */
    void executeRule();
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
