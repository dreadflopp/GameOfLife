/**
 * @file RuleFactory.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date 2017-10-29
 * @version 0.1
*/

#ifndef RULEFACTORY_H
#define RULEFACTORY_H

#include "GoL_Rules/RuleOfExistence.h"

/**
 * @class RuleFactory singleton class to handle creation of RulesOfExistence objects
 * @brief singleton class makes sure only one RuleFactory object is created which then can create and
 * return specified RuleOfExistance objects
 * @test that only one instance of class can be created
 */
class RuleFactory
{
private:
    RuleFactory() {}

public:
    /**
     * @brief function that creates RuleFactory object and returns reference to that object
     * @return reference to RuleFactory object
     */
    static RuleFactory& getInstance();
    /**
     * @brief function creates RuleOfExistance objects
     * @details function creates RuleOfExistance object(rules) based on param ruleName
     * @param cells passed by reference and represents cells in population which rules should be applied to
     * @param ruleName represents rule to be applied. Default is 'conway'
     * @return pointer to RuleOfExistance object
     * @test that new rule has been created as expected
     */
    RuleOfExistence* createAndReturnRule(map<Point, Cell>& cells, string ruleName = "conway");
};

#endif