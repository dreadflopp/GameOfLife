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
#include <Support/MainArguments.h>
#include <Support/MainArgumentsParser.h>
#include <Support/FileLoader.h>
#include "catch.hpp"
#include "memstat.hpp"
#include "GoL_Rules/RuleOfExistence.h"


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
                    REQUIRE(a < b);
                }
        }
        WHEN("The x value of point a is more than the x value of point b") {
            if (ax > bx)
                THEN("point b should be less than point a") {
                    REQUIRE(b < a);
                }
        }
        WHEN("The x value of point a is equal to the x value of point b") {
            if (ax == bx) {
                AND_WHEN("The y value of point a is less than the y value of point b") {
                    if (ay < by) {
                        THEN("point a should be less than point b") {
                            REQUIRE(a < b);
                        }
                    }
                }
                AND_WHEN("The y value of point a is more than the y value of point b") {
                    if (ay > by) {
                        THEN("point b should be less than point a") {
                            REQUIRE(b < a);
                        }
                    }
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

/*
 * Testing BaseArguments and its derived clases
 */
SCENARIO("Testing the class HelpArgument") {
    GIVEN("A HelpArgument object and an ApplicationValues struct where runSimulation is set to true") {
        HelpArgument helpArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;
        char* ch;

        WHEN("The class is executed") {
            helpArg.execute(appValues, ch);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
        }
    }
}

SCENARIO("Testing GenerationsArgument") {
    GIVEN("A GenerationsArgument object and an ApplicationValues struct where runSimulation is set to true") {
        GenerationsArgument genArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;

        WHEN("The object is executed when generations is not set") {
            char* generations=nullptr;
            genArg.execute(appValues, generations);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
            AND_WHEN("the object is executed again with generations set to a value") {
                generations = "97";
                genArg.execute(appValues, generations);
                THEN("appValues.maxGenerations should be set") {
                    REQUIRE(appValues.maxGenerations == 97);
                }
            }
        }
    }
}

SCENARIO("Testing the class WorldSizeArgument") {
    GIVEN("A class object and an ApplicationValues struct") {
        WorldsizeArgument worldArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;

        WHEN("The object is executed and dimensions is not set") {
            char* dimensions=nullptr;
            worldArg.execute(appValues, dimensions);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
            AND_WHEN("executing the with dimensions is set to a valid value") {
                dimensions = "79x34";
                worldArg.execute(appValues, dimensions);
                THEN("the WORLD_DIMENSIONS should be 79x34") {

                    REQUIRE(WORLD_DIMENSIONS.HEIGHT == 34);
                    REQUIRE(WORLD_DIMENSIONS.WIDTH == 79);
                }
            }
        }
    }
}

SCENARIO("Testing FileArgument") {
    GIVEN("A FileArgument object and an ApplicationValues struct where runSimulation is set to true") {
        FileArgument fileArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;

        WHEN("The object is executed when fileNameArg is not set") {
            char* fileNameArg=nullptr;
            fileArg.execute(appValues, fileNameArg);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
            AND_WHEN("the object is executed again with fileNameArg set to a value") {
                fileNameArg = "testName";
                fileArg.execute(appValues, fileNameArg);
                THEN("the global variable FileName should be equal to fileNameArg") {
                    REQUIRE(fileName == fileNameArg);
                }
            }
        }
    }
}

SCENARIO("Testing EvenRuleArgument") {
    GIVEN("An EvenRuleArgument object and an ApplicationValues struct where runSimulation is set to true") {
        EvenRuleArgument evenArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;

        WHEN("The object is executed when argument is not set") {
            char* argument=nullptr;
            evenArg.execute(appValues, argument);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
            AND_WHEN("the object is executed again with argument set to a value") {
                argument = "testName";
                evenArg.execute(appValues, argument);
                THEN("appValues.evenRuleName  should be equal to argument") {
                    REQUIRE(appValues.evenRuleName == argument);
                }
            }
        }
    }
}

SCENARIO("Testing OddRuleArgument") {
    GIVEN("An OddRuleArgument object and an ApplicationValues struct where runSimulation is set to true") {
        OddRuleArgument oddArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;

        WHEN("The object is executed when argument is not set") {
            char* argument=nullptr;
            oddArg.execute(appValues, argument);
            THEN("appValues.runSimulation should be false") {
                REQUIRE(appValues.runSimulation == false);
            }
            AND_WHEN("the object is executed again with argument set to a value") {
                argument = "testName";
                oddArg.execute(appValues, argument);
                THEN("appValues.evenRuleName  should be equal to argument") {
                    REQUIRE(appValues.oddRuleName == argument);
                }
            }
        }
    }
}

/*
 * Testing FileLoader
 */
SCENARIO("Testing that a missing file throws an error") {
    GIVEN("A FileLoader object and a map of cells to load into") {
        FileLoader fileLoader;
        map<Point, Cell> cells;
        WHEN("The file doesn't exist") {
            // Pretty random string
            std::string prettyRandom = "olauhgfal£@$€ouirhjfgliSDRjhp3wsdf29845u6tp";
            std::random_shuffle(prettyRandom.begin(), prettyRandom.end());

            fileName = prettyRandom;
            THEN("Loading the file should throw an error") {
                REQUIRE_THROWS(fileLoader.loadPopulationFromFile(cells));
            }
        }
    }
}
