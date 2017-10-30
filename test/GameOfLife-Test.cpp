/*
 * file GameOfLife-Test.cpp
 * author Mattias Lindell
 * author Andreas Lind
 * date 29 october 2017
 * version 0.1
*/
#include "catch.hpp"
#include "memstat.hpp"
#include "GoL_Rules/RuleOfExistence.h"
#include <string>
#include <vector>
#include <GoL_Rules/RuleFactory.h>

using namespace std;

/*
 * TESTING class RuleFactory
 */
SCENARIO("Before creating RuleFactory object") {
    GIVEN("An empty RuleOfExistance object") {
        RuleOfExistence *testRule(nullptr);

        THEN("No rule should exist"){
            REQUIRE(testRule == nullptr);
        }
        WHEN("Rulefactory object is created and rules are created") {
            map<Point, Cell> cells;
            vector<string> testStrings = {"erik", "von_neumann", "andreas", "mattias", ""}; //input different strings to test that predefined rules are applied as
                                                                                            //well as undefined rules which will result in default rules
            for (auto e: testStrings) {
                testRule = RuleFactory::getInstance().createAndReturnRule(cells, e); //ruleFactory object is created and returned by reference when getInstance() is called

                AND_WHEN("The rule is set to be Eriks rules") {
                    if (e == "erik") {
                        THEN("Rulename should be set to erik") {
                            REQUIRE(testRule->getRuleName() == "erik");
                        }
                    }
                }

                AND_WHEN("The rule is set to be VonNeumanns rules") {
                    if (e == "von_neumann") {
                        THEN("Rulename should be set to von_neumann") {
                            REQUIRE(testRule->getRuleName() == "von_neumann");
                        }
                    }
                }

                AND_WHEN("Neither Eriks or VonNeumanns rules should be applied") {
                    if(e != "erik" && e != "von_neumann"){
                        THEN("Rule should be Conways rules") {
                            REQUIRE(testRule->getRuleName() == "conway");
                        }
                    }
                }
                delete testRule; //manually deallocate RuleOfExistance object since they are deallocated in Population-destructor in real simulation
            }
        }
    }
}