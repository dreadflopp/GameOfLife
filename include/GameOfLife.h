/**
 * @file GameOfLife.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date 2017-10-27
 * @version 0.1
*/

#ifndef GameOfLifeH
#define GameOfLifeH

#include "Cell_Culture/Population.h"
#include "ScreenPrinter.h"
#include <string>
/**
 * @class GameOfLife
 * @brief The heart of the simulation, interconnects the main execution with the graphical presentation.
 * @details Creates and manages Population and the ScreenPrinter instances. Will instruct the Population of cells to keep
 * updating as long as the specified number of generations is not reached, and for each iteration instruct
 * ScreenPrinter to write the information on screen.
 */
class GameOfLife {

private:
    Population population;
    ScreenPrinter& screenPrinter;
    int nrOfGenerations;

public:
    /**
     *  @brief Constructor that initializes GameOfLife object with max nr of generations and rules for simulation
     *  @param nrOfGenerations represents nr of genererations the simulation should iterate over before application ends. Default = 100
     *  @param evenRuleName represents rules to be applied to every even numbered generation of cells. Default = 'Conway'
     *  @param oddRuleName represents rules to be applied to every odd numbered generation of cells. Default = evenRuleName
     *  @test that data members are correctly set with different set of inputs
     */
    GameOfLife(int nrOfGenerations, string evenRuleName, string oddRuleName);
     /**
     *  @brief initiates the simulation and prints the first generation of cells and then continues to print the next
     *  generation until the maximum number of generations has been reached
     *  @test that correct nr of generations are printed out
     */
    void runSimulation();

};

#endif
