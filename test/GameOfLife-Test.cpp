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
#include <fstream>

/*
 * TESTING class RuleOfExistence_Erik
 */
SCENARIO("Testing RuleOfExistence_Erik") {
    GIVEN("A cell culture with no more than 3 neighbours to each cell") {
        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |#0#|1
         * |000|2
         * |#00|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, IGNORE_CELL);
        cellMap[Point{2, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{2, 3}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        cells.initiateTestPopulation(cellMap, "erik", "erik");
        cells.calculateNewGeneration();

        // Age some cells


        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected and that all cells with less than 3 neighbours are killed") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |000|1
                 * |0#0|2
                 * |000|3
                 * -------
                 */

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 1}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{1, 1}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{1, 3}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).getColor() == STATE_COLORS.DEAD);

                REQUIRE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).getColor() == STATE_COLORS.LIVING);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{3, 3}).getColor() == STATE_COLORS.DEAD);
            }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();

                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                     * The cell structure should look like this:
                     * 0123
                     * -----0
                     * |000|1
                     * |000|2
                     * |000|3
                     * -------
                     */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 1}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 2}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 3}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 2}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 3}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 1}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 3}).getColor() == STATE_COLORS.DEAD);
                }
            }

        }
    }
    GIVEN("A cell culture with living cells with more than 3 neighbours") {

        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |#0#|1
         * |##0|2
         * |##0|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 3}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        // Age cell {1, 1}
        for(int i = 0; i < 10; i++) {
            cellMap.at(Point{1, 1}).updateState();
            cellMap.at(Point{1, 1}).setNextGenerationAction(IGNORE_CELL);
        }

        // Age cell {3, 1}
        for(int i = 0; i < 9; i++) {
            cellMap.at(Point{3, 1}).updateState();
            cellMap.at(Point{3, 1}).setNextGenerationAction(IGNORE_CELL);
        }

        cells.initiateTestPopulation(cellMap, "erik", "erik");
        cells.calculateNewGeneration();
        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected, that all cells with less than 3 neighbours are killed and that cells with more than 4 neighbours are killed and that colors are changed and and elders are created as they should") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |#00|1
                 * |00#|2
                 * |##0|3
                 * -------
                 */

                REQUIRE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 1}).getCellValue() == 'E');
                REQUIRE(cells.getCellAtPosition(Point{1, 1}).getColor() == STATE_COLORS.ELDER);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{1, 3}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).getColor() == STATE_COLORS.DEAD);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).getColor() == STATE_COLORS.DEAD);

                REQUIRE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).getColor() == STATE_COLORS.LIVING);

                REQUIRE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).getCellValue() == 'E');
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).getColor() == STATE_COLORS.OLD);

                REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).getColor() == STATE_COLORS.LIVING);

                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 3}).getCellValue() == '#');
                REQUIRE(cells.getCellAtPosition(Point{3, 3}).getColor() == STATE_COLORS.DEAD);
         }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();
                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |000|1
                 * |#00|2
                 * |0#0|3
                 * -------
                 */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 1}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 2}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{1, 3}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).getColor() == STATE_COLORS.LIVING);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 2}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{2, 3}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 1}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 1}).getColor() == STATE_COLORS.DEAD);

                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).getColor() == STATE_COLORS.LIVING);

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 3}).getCellValue() == '#');
                    REQUIRE(cells.getCellAtPosition(Point{3, 3}).getColor() == STATE_COLORS.DEAD);
                }
            }
        }

    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
}

/*
/*
 * TESTING class Population
 */
SCENARIO("Testing a Population object") {
    GIVEN("An empty Population object") {
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
                evenRuleName = allRules.at(static_cast<unsigned long>(random(generator) % 3));
                string oddRuleName;
                oddRuleName = allRules.at(static_cast<unsigned long>(random(generator) % 3));
                myPopulation.initiatePopulation(evenRuleName, oddRuleName);

                THEN("data member evenRuleOfExistence should be evenRuleName") {
                    REQUIRE(myPopulation.getEvenRuleName() == evenRuleName);
                }
                THEN("data member oddRuleOfExistence should be oddRuleName") {
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
SCENARIO("Testing that if Population is read from file, stored cells in Population are a copy of the cell structure in the file"){
    GIVEN("Population created from file and a local copy saved in vector for cell comparison"){
        fileName = "../Population_Seed.txt";
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

        vector<int> testCells;

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

        int pos_in_vec = 0;
        int testValue;
        THEN("Values in population should be a replica of values in vector"){
            for(int row = 1; row < height + 1; row++){
                for(int column = 1; column < width + 1; column++)
                {
                    testValue = testCells[pos_in_vec];
                    WHEN("Value in vector is '0'") {
                        THEN("cell in corresponding place in Population should NOT be alive") {
                            if (testValue == 0) {
                                REQUIRE_FALSE(myPopulation.getCellAtPosition(Point{row, column}).isAlive());
                            }
                        }
                    }
                    WHEN("Value in vector is '1'") {
                        THEN("cell in corresponding place in Population should be alive") {
                            if (testValue == 1) {
                                REQUIRE(myPopulation.getCellAtPosition(Point{row, column}).isAlive());
                            }
                        }
                    }
                    pos_in_vec++;
                }
            }
        }
    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
    fileName.clear();
}
/*
 * TESTING class MainArgumentsParser
 */
SCENARIO("Testing MainArgumentsParser with default values") {
    GIVEN("MainArgumentsParser object") {
        MainArgumentsParser parser;

        WHEN("Given no input values"){
            char *argv[] = {const_cast<char*>("GameOfLife")};
            int argc = 1;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("runSimulation should be true") {
                REQUIRE(appValues.runSimulation);
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
            char *argv[] = {const_cast<char*>("GameOfLife"), const_cast<char*>("-s"), const_cast<char*>("160x24"), const_cast<char*>("-er"), const_cast<char*>("erik"), const_cast<char*>("-or"), const_cast<char*>("von_neumann"), const_cast<char*>("-g"), const_cast<char*>("500"), const_cast<char*>("-f"), const_cast<char*>("population.txt")};
            int argc = 11;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("runSimulation should be true") {
                REQUIRE(appValues.runSimulation);
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
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
    fileName.clear();
}

SCENARIO("Testing MainArgumentsParser with missing value") {
    GIVEN("MainArgumentsParser object") {
        MainArgumentsParser parser;

        WHEN("Given indicator '-g' to set generations but no value"){
            char *argv[] = {const_cast<char*>("GameOfLife"), const_cast<char*>("-g")};
            int argc = 2;
            ApplicationValues appValues = parser.runParser(argv, argc);
            THEN("simulation should close") {
                REQUIRE_FALSE(appValues.runSimulation);
            }
        }
    }
}

/*
 * Testing the struct Point
 */
SCENARIO ("Testing the overloading of operator < in the struct Point") {
    GIVEN("Two random points") {
        std::default_random_engine generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int> random(1, 1000);
        int ax = random(generator);
        int ay = random(generator);
        int bx = random(generator);
        int by = random(generator);

        Point a = {ax, ay};
        Point b = {bx, by};

        WHEN("The x value of point a is less than the x value of point b") {
            if (ax < bx) {
                THEN("point a should be less than point b") {
                    REQUIRE(a < b);
                    REQUIRE_FALSE(a == b);
                }
            }
        }
        WHEN("The x value of point a is more than the x value of point b") {
            if (ax > bx) {
                THEN("point b should be less than point a") {
                    REQUIRE(b < a);
                    REQUIRE_FALSE(a == b);
                }
            }
        }
        WHEN("The x value of point a is equal to the x value of point b") {
            if (ax == bx) {
                AND_WHEN("The y value of point a is less than the y value of point b") {
                    if (ay < by) {
                        THEN("point a should be less than point b") {
                            REQUIRE(a < b);
                            REQUIRE_FALSE(a == b);
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
                AND_WHEN("The y value of point a is equal to the y value of point b") {
                    if ( ay == by) {
                        THEN("The point should be equal") {
                            REQUIRE(a == b);
                        }
                    }
                }
            }
        }
    }
    GIVEN("Two equal points") {
        std::default_random_engine generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int> random(1, 1000);
        int ax = random(generator);
        int ay = random(generator);

        Point a = {ax, ay};
        Point b = {ax, ay};
        THEN("The point should be equal") {
            REQUIRE( a == b);
        }
    }
}

/*
 * TESTING class RuleFactory
 */
SCENARIO("Before creating RuleFactory object") {
    GIVEN("An empty RuleOfExistence object") {
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
                delete testRule; //manually deallocate RuleOfExistence object since they are deallocated in Population-destructor in real simulation
            }
        }
    }
}

/*
 * Testing BaseArguments and its derived classes
 */
SCENARIO("Testing the class HelpArgument") {
    GIVEN("A HelpArgument object and an ApplicationValues struct where runSimulation is set to true") {
        HelpArgument helpArg;
        ApplicationValues appValues;
        appValues.runSimulation = true;
        char* ch = const_cast<char *>("");

        WHEN("The class is executed") {
            helpArg.execute(appValues, ch);
            THEN("appValues.runSimulation should be false") {
                REQUIRE_FALSE(appValues.runSimulation);
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
                REQUIRE_FALSE(appValues.runSimulation);
            }
            AND_WHEN("the object is executed again with generations set to a value") {
                generations = const_cast<char *>("97");
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
                REQUIRE_FALSE(appValues.runSimulation);
            }
            AND_WHEN("executing the with dimensions is set to a valid value") {
                dimensions = const_cast<char *>("79x34");
                worldArg.execute(appValues, dimensions);
                THEN("the WORLD_DIMENSIONS should be 79x34") {

                    REQUIRE(WORLD_DIMENSIONS.HEIGHT == 34);
                    REQUIRE(WORLD_DIMENSIONS.WIDTH == 79);
                }
            }
        }
    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
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
                REQUIRE_FALSE(appValues.runSimulation);
            }
            AND_WHEN("the object is executed again with fileNameArg set to a value") {
                fileNameArg = const_cast<char *>("testName");
                fileArg.execute(appValues, fileNameArg);
                THEN("the global variable FileName should be equal to fileNameArg") {
                    REQUIRE(fileName == fileNameArg);
                }
            }
        }
    }
    //RESET globals
    fileName.clear();
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
                REQUIRE_FALSE(appValues.runSimulation);
            }
            AND_WHEN("the object is executed again with argument set to a value") {
                argument = const_cast<char *>("testName");
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
                REQUIRE_FALSE(appValues.runSimulation);
            }
            AND_WHEN("the object is executed again with argument set to a value") {
                argument = const_cast<char *>("testName");
                oddArg.execute(appValues, argument);
                THEN("appValues.evenRuleName  should be equal to argument") {
                    REQUIRE(appValues.oddRuleName == argument);
                }
            }
        }
    }
}

/*
 * Tests for Cell
 */
SCENARIO("Testing that the class Cell works as it should") {
    GIVEN("A dead cell that is not a rim cell") {
        Cell cell;
        THEN("The cell should be dead") {
            REQUIRE_FALSE(cell.isAlive());
        }
        THEN("The cells age should be 0") {
            REQUIRE(cell.getAge() == 0);
        }
        THEN("The cell should not be a rim cell") {
            REQUIRE_FALSE(cell.isRimCell());
        }
        THEN("The next action should be set to it's default") {
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }
        WHEN("Giving the cell life") {
            cell.setNextGenerationAction(GIVE_CELL_LIFE);
            THEN("The next action should be correctly set to give the cell life") {
                REQUIRE(cell.getNextGenerationAction() == GIVE_CELL_LIFE);
            }
            AND_WHEN("The cells state gets updated") {
                cell.updateState();
                THEN("The cell should be alive") {
                    REQUIRE(cell.isAlive());
                }
                THEN("The cell should have the age 1") {
                    REQUIRE(cell.getAge() == 1);
                }
                THEN("The cell should not be a rim cell") {
                    REQUIRE_FALSE(cell.isRimCell());
                }
                THEN("The next action should be reset") {
                    REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                }
                AND_WHEN("The cell action is set to be ignored") {
                    cell.setNextGenerationAction(IGNORE_CELL);
                    THEN("The next action should be set to be ignored") REQUIRE(
                                cell.getNextGenerationAction() == IGNORE_CELL);
                    AND_WHEN("The cell state gets update") {
                        cell.updateState();
                        THEN("The cells age should have been increased by 1") {
                            REQUIRE(cell.getAge() == 2);
                        }
                        THEN("The cell should not be a rim cell") {
                            REQUIRE_FALSE(cell.isRimCell());
                        }
                        THEN("The next action should be reset") {
                            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                        }
                        AND_WHEN("Setting the color of the cell and updating") {
                            // Random generator
                            std::default_random_engine generator(static_cast<unsigned>(time(0)));
                            std::uniform_int_distribution<int> random(0, 3);

                            // A vector of colors
                            vector<COLOR> colors = {STATE_COLORS.DEAD, STATE_COLORS.LIVING, STATE_COLORS.ELDER,
                                                    STATE_COLORS.OLD};

                            // Assign random color
                            COLOR nextColor = colors.at(static_cast<unsigned long>(random(generator)));
                            cell.setNextColor(nextColor);
                            cell.updateState();
                            THEN("The color of the cell should be correctly set") {
                                REQUIRE(cell.getColor() == nextColor);
                            }
                            THEN("The cells age should not have increased since the action was DO_NOTHING") {
                                REQUIRE(cell.getAge() == 2);
                            }
                            THEN("The cell should not be a rim cell") {
                                REQUIRE_FALSE(cell.isRimCell());
                            }
                            AND_WHEN("Setting the value of the cell and updating") {
                                // Random char
                                std::uniform_int_distribution<int> random_char(33, 126);
                                auto value = static_cast<char>(random_char(generator));

                                // Assign random char
                                cell.setNextCellValue(value);
                                cell.updateState();
                                THEN("The value of the cell should be correctly set") {
                                    REQUIRE(cell.getCellValue() == value);
                                }
                                THEN("The cells age should not have increased since the action was DO_NOTHING") {
                                    REQUIRE(cell.getAge() == 2);
                                }
                                THEN("The cell should not be a rim cell") {
                                    REQUIRE_FALSE(cell.isRimCell());
                                }
                                AND_WHEN("Finally killing the cell") {
                                    cell.setNextGenerationAction(KILL_CELL);
                                    cell.updateState();
                                    THEN("The cells age should have been reset") {
                                        REQUIRE(cell.getAge() == 0);
                                    }
                                    THEN("The cell should not be a rim cell") {
                                        REQUIRE_FALSE(cell.isRimCell());
                                    }
                                    THEN("The next action should be reset") {
                                        REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        WHEN("Setting is alive next to true") {
            cell.setIsAliveNext(true);
            THEN("The cell should be set to be alive next") {
                REQUIRE(cell.isAliveNext());
            }
            AND_WHEN("Setting is alive next to false") {
                cell.setIsAliveNext(false);
                THEN("The cell should not be set to be alive next") {
                    REQUIRE_FALSE(cell.isAliveNext());
                }
            }
        }
    }
    GIVEN("A rim cell") {
        Cell cellRim(true);
        WHEN("Giving the cell life") {
            cellRim.setNextGenerationAction(GIVE_CELL_LIFE);
            THEN("The cell should NOT be set to come alive, since it is a rim cell") {
                REQUIRE(cellRim.getNextGenerationAction() == DO_NOTHING);
            }
            AND_WHEN("Updating the cell") {
                cellRim.updateState();
                THEN("The cell age should be 0 since it is a rim cell") {
                    REQUIRE(cellRim.getAge() == 0);
                }
                THEN("The next action should be reset") {
                    REQUIRE((cellRim.getNextGenerationAction() == DO_NOTHING));
                }
            }
        }
    }
    GIVEN("Two random Cells and a third one equal to the second") {
        std::default_random_engine generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int> random(0, 99999);
        std::uniform_int_distribution<int> random_char(33, 126);

        auto actionFirst = static_cast<ACTION>(random(generator)%5);
        auto isRimCellFirst = static_cast<bool>(random(generator)%2);
        auto colorFirst = static_cast<COLOR>(random(generator)%8);
        auto valueFirst = static_cast<char>(random_char(generator));
        Cell cellFirst(isRimCellFirst, actionFirst);
        cellFirst.setNextCellValue(valueFirst);
        cellFirst.setNextColor(colorFirst);

        auto actionSecond = static_cast<ACTION>(random(generator)%5);
        auto isRimCellSecond = static_cast<bool>(random(generator)%2);
        auto colorSecond = static_cast<COLOR>(random(generator)%8);
        auto valueSecond = static_cast<char>(random_char(generator));
        Cell cellSecond(isRimCellSecond, actionSecond);
        cellSecond.setNextCellValue(valueSecond);
        cellSecond.setNextColor(colorSecond);
        Cell cellThird(isRimCellSecond, actionSecond);
        cellThird.setNextCellValue(valueSecond);
        cellThird.setNextColor(colorSecond);

        WHEN("All values are equal") {
            if (actionFirst == actionSecond && isRimCellFirst == isRimCellSecond && colorFirst == colorSecond &&
                valueFirst == valueSecond) {
                THEN("The cells should be equal") {
                    REQUIRE(cellFirst == cellSecond);
                }
            }
            AND_WHEN("All values aren't equal") {
                if (actionFirst != actionSecond || isRimCellFirst != isRimCellSecond || colorFirst != colorSecond ||
                    valueFirst != valueSecond) {
                    THEN("The cells shouldn't be equal") {
                        REQUIRE_FALSE(cellFirst == cellSecond);
                    }
                }
            }
        }
        WHEN("All values are equal") {
            THEN("The cells should be equal") {
                REQUIRE(cellSecond == cellThird);
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
            std::shuffle(prettyRandom.begin(), prettyRandom.end(), std::mt19937(std::random_device()()));

            fileName = prettyRandom;
            THEN("Loading the file should throw an error") {
                REQUIRE_THROWS(fileLoader.loadPopulationFromFile(cells));
            }
        }
        WHEN("The file does exist") {
            fileName = "../Population_Seed.txt";
            THEN("Loading the file should not throw an error") {
                REQUIRE_NOTHROW(fileLoader.loadPopulationFromFile(cells));
            }
        }
    }

    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
    fileName.clear();
}

/*
 * Testing RuleOfExistence_Conway
 */
SCENARIO("Testing RuleOfExistence_Conway") {
    GIVEN("A cell culture with no more than 3 neighbours to each cell") {
        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |101|1
         * |000|2
         * |100|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, IGNORE_CELL);
        cellMap[Point{2, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{2, 3}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        cells.initiateTestPopulation(cellMap, "conway", "conway");
        cells.calculateNewGeneration();
        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected and that all cells with less than 3 neighbours are killed") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |000|1
                 * |010|2
                 * |000|3
                 * -------
                 */

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
            }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();

                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                     * The cell structure should look like this:
                     * 0123
                     * -----0
                     * |000|1
                     * |000|2
                     * |000|3
                     * -------
                     */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                }
            }

        }
    }
    GIVEN("A cell culture with living cells with more than 3 neighbours") {

        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |101|1
         * |110|2
         * |110|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 2}] = Cell(false, IGNORE_CELL);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 3}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        cells.initiateTestPopulation(cellMap, "conway", "conway");
        cells.calculateNewGeneration();
        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected, that all cells with less than 3 neighbours are killed and that cells with more than 4 neighbours are killed") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |100|1
                 * |001|2
                 * |110|3
                 * -------
                 */

                REQUIRE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
            }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();
                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |000|1
                 * |100|2
                 * |010|3
                 * -------
                 */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                }
            }
        }

    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
}

/*
 * Testing RuleOfExistence_VonNeuman
 */
SCENARIO("Testing RuleOfExistence_VonNeuman") {
    GIVEN("A cell culture with no more than 3 neighbours to each cell") {
        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |111|1
         * |010|2
         * |110|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, IGNORE_CELL);
        cellMap[Point{2, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 3}] = Cell(false, IGNORE_CELL);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        cells.initiateTestPopulation(cellMap, "von_neumann", "von_neumann");
        cells.calculateNewGeneration();
        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected and that all cells with less than 3 neighbours are killed") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |010|1
                 * |110|2
                 * |010|3
                 * -------
                 */

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
            }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();

                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                     * The cell structure should look like this:
                     * 0123
                     * -----0
                     * |000|1
                     * |010|2
                     * |000|3
                     * -------
                     */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                }
            }

        }
    }
    GIVEN("A cell culture with living cells with more than 3 neighbours") {

        // the world
        WORLD_DIMENSIONS.HEIGHT = 3;
        WORLD_DIMENSIONS.WIDTH = 3;

        // the cells
        map<Point, Cell> cellMap;
        Population cells;
        /*
         * The cell structure:
         * 0123
         * -----0
         * |011|1
         * |111|2
         * |110|3
         * -------
         */
        cellMap[Point{1, 1}] = Cell(false, IGNORE_CELL);
        cellMap[Point{1, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{1, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{2, 3}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 1}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 2}] = Cell(false, GIVE_CELL_LIFE);
        cellMap[Point{3, 3}] = Cell(false, IGNORE_CELL);

        cells.initiateTestPopulation(cellMap, "von_neumann", "von_neumann");
        cells.calculateNewGeneration();
        WHEN("A new generation is calculated to check if cells with 3 neighbours are resurrected, that all cells with less than 3 neighbours are killed and that cells with more than 4 neighbours are killed") {
            cells.calculateNewGeneration();
            THEN("The cell structure should update and resurrect and kill the correct cells") {
                /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |011|1
                 * |101|2
                 * |110|3
                 * -------
                 */

                REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                REQUIRE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
            }
            AND_WHEN("A new generation is calculated") {
                cells.calculateNewGeneration();
                THEN("The cell structure should update and resurrect and kill the correct cells") {
                    /*
                 * The cell structure should look like this:
                 * 0123
                 * -----0
                 * |001|1
                 * |000|2
                 * |100|3
                 * -------
                 */

                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{1, 2}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{1, 3}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{2, 3}).isAlive());
                    REQUIRE(cells.getCellAtPosition(Point{3, 1}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 2}).isAlive());
                    REQUIRE_FALSE(cells.getCellAtPosition(Point{3, 3}).isAlive());
                }
            }
        }

    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
}

/*
 * Testing ScreenPrinter
 */
SCENARIO("Testing ScreenPrinter") {
    GIVEN("A population") {
        default_random_engine generator(static_cast<unsigned>(time(0)));
        uniform_int_distribution<int> random_0_1(0, 1);
        uniform_int_distribution<int> random_0_2(0, 2);

        // allocate and map cells based on worldSize
        map<Point, Cell> cellsMap;
        WORLD_DIMENSIONS.HEIGHT = 20;
        WORLD_DIMENSIONS.WIDTH = 20;

        for (int row = 0; row <= WORLD_DIMENSIONS.HEIGHT + 1; row++) {

            for (int column = 0; column <= WORLD_DIMENSIONS.WIDTH + 1; column++) {
                // if cell is a rim cell
                if (column == 0 || row == 0
                    || column == WORLD_DIMENSIONS.WIDTH + 1
                    || row == WORLD_DIMENSIONS.HEIGHT + 1) {

                    cellsMap[Point{column, row}] = Cell(true); // create a cell with rimCell state set to true
                }
                else { // If cell is an ordinary cell
                    if (random_0_1(generator)) { // Randomly pick alive/dead
                        cellsMap[Point{column, row}] = Cell(false, GIVE_CELL_LIFE); // create a ordinary living cell
                    }
                    else {
                        cellsMap[Point{column, row}] = Cell(false, IGNORE_CELL); // else create a ordinary dead cell
                    }
                }
            }
        }

        // initiate the population
        Population cells;
        vector<string> rules = { "conway", "erik", "von_neumann"};
        unsigned long rule1 = random_0_2(generator);
        unsigned long rule2 = random_0_2(generator);
        cells.initiateTestPopulation(cellsMap, rules.at(rule1), rules.at(rule2));
        WHEN("Printing the population to the screen") {
            ScreenPrinter screenPrinter = ScreenPrinter::getInstance();
            screenPrinter.printBoard(cells);
            THEN("The population should be unchanged") {
                map<Point, Cell> newCellsMap = cells.getCells();
                REQUIRE(newCellsMap == cellsMap);
            }
        }
    }
    //RESET globals
    WORLD_DIMENSIONS.WIDTH = 80;
    WORLD_DIMENSIONS.HEIGHT = 24;
}
