/*
 * file GameOfLife-Test.cpp
 * author Mattias Lindell
 * author Andreas Lind
 * date 29 october 2017
 * version 0.1
*/
#include <random>
#include <Support/SupportStructures.h>
#include <GoL_Rules/RuleFactory.h>
#include <Support/MainArgumentsParser.h>
#include "catch.hpp"
#include "memstat.hpp"
#include "GoL_Rules/RuleOfExistence.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GameOfLife.h>

/*
 * TESTING class Population
 */
SCENARIO("Testing a Population object") {
    GIVEN("A Population object") {
        Population myPopulation;
        WHEN("Population object is created") {
            THEN("Population should be empty") {
                REQUIRE(myPopulation.getTotalCellPopulation() == 0);
            }
            AND_WHEN("Population is initiated with randomly created cells and randomly chosen valid rulenames") {
                // Random generator
                std::default_random_engine generator(static_cast<unsigned>(time(0)));
                std::uniform_int_distribution<int> random(1, 999999);

                // Randomize rules
                vector<string> allRules = {"conway", "erik", "von_neumann"};

                string evenRuleName;
                evenRuleName = allRules.at(random(generator) % 3);
                string oddRuleName;
                oddRuleName = allRules.at(random(generator) % 3);
                myPopulation.initiatePopulation(evenRuleName, oddRuleName);

                THEN("data member evenRuleOfExistance should be evenRuleName") {
                    REQUIRE(myPopulation.getEvenRuleName() == evenRuleName);
                }
                THEN("data member oddRuleOfExistance should be oddRuleName") {
                    REQUIRE(myPopulation.getOddRuleName() == oddRuleName);
                }
                THEN("Population should not be empty") {
                    REQUIRE(myPopulation.getTotalCellPopulation() > 0);
                }
                AND_WHEN("when calculateNewGeneration is run"){
                    int testGen = 0;
                    testGen = myPopulation.calculateNewGeneration();
                    THEN("generation is incremented by 1") {
                        REQUIRE(testGen == 1);
                    }
                }
            }
        }
    }
}
/* UNFINISHED TEST
SCENARIO("Testing that if Population is read from file, stored cells in Population are a copy of the cell structure in the file"){
    GIVEN("Population created from file and a local copy for cell comparison"){
        fileName = "Population_Seed.txt";
        Population myPopulation;
        myPopulation.initiatePopulation("erik", "von_neumann");

        ifstream inFile(fileName);
        string worldSize;
        getline(inFile, worldSize);

        int width = 0, height = 0;
        istringstream iss(worldSize);
        iss >> width;
        iss.get();
        iss >> height;
        iss.clear();

        vector<char> testCells;

        for (int row = 0; row < height; row++) {
            string populationRow;
            getline(inFile, populationRow);
            iss.str(populationRow);

            for (int column = 0; column < width; column++) {
                testCells.push_back(iss.get());
                iss.clear();
            }
        }
        inFile.close();
    }
}
*/
/*
 * TESTING class MainArgumentsParser
 */
SCENARIO("Testing MainArgumentsParser with default values") {
    GIVEN("MainArgumentsParser object") {
        MainArgumentsParser parser;

        WHEN("Given no input values"){
            char *argv[] = {"GameOfLife"};
            int argc = 1;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("runSimulation should be true") {
                REQUIRE(appValues.runSimulation == true);
                AND_THEN("maxGenerations should be set to default '100'") {
                    REQUIRE(appValues.maxGenerations == 100);
                }
                AND_THEN("evenRuleName should be set to default 'conway'") {
                    REQUIRE(appValues.evenRuleName == "conway");
                }
                AND_THEN("oddRuleName should copy evenRuleName") {
                    REQUIRE(appValues.oddRuleName == appValues.evenRuleName);
                }
                AND_THEN("WORLD_DIMENSIONS should be set to default 80x24") {
                    REQUIRE(WORLD_DIMENSIONS.WIDTH == 80);
                    REQUIRE(WORLD_DIMENSIONS.HEIGHT == 24);
                }
            }
        }
    }
}
SCENARIO("Testing MainArgumentsParser with all possible parameters"){
    GIVEN("MainArgumentsParser object") {
        MainArgumentsParser parser;

        WHEN("Given valid set of input values to set WORLD_DIMENSIONS, evenRuleName, oddRuleName, generations, filename") {
            char *argv[] = {"GameOfLife", "-s", "160x24", "-er", "erik", "-or", "von_neumann", "-g", "500", "-f", "population.txt"};
            int argc = 11;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("runSimulation should be true") {
                REQUIRE(appValues.runSimulation == true);
                AND_THEN("MaxGenerations should be set to '500'") {
                    REQUIRE(appValues.maxGenerations == 500);
                }
                AND_THEN("evenRuleName should be set to 'erik'") {
                    REQUIRE(appValues.evenRuleName == "erik");
                }
                AND_THEN("evenRuleName should be set to 'von_neumann'") {
                    REQUIRE(appValues.oddRuleName == "von_neumann");
                }
                AND_THEN("global fileName should be set to 'population.txt'") {
                REQUIRE(fileName == "population.txt");
                }
                AND_THEN("WORLD_DIMENSIONS should be set to '160x24'") {
                    REQUIRE(WORLD_DIMENSIONS.WIDTH == 160);
                    REQUIRE(WORLD_DIMENSIONS.HEIGHT == 24);
                }
            }
        }
    }
}

SCENARIO("Testing MainArgumentsParser with missing value") {
    GIVEN("MainArgumentsParser object") {
        MainArgumentsParser parser;

        WHEN("Given indicator '-g' to set generations but no value"){
            char *argv[] = {"GameOfLife", "-g"};
            int argc = 2;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("simulation should close") {
                REQUIRE(appValues.runSimulation == false);
            }
        }
    }
}

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

