/**
 * @file ScreenPrinter.h
 * @author Andreas Lind
 * @author Mattias Lindell
 * @date October 2017
 * @version 0.1
*/



#ifndef screenPrinterH
#define screenPrinterH


#include "../terminal/terminal.h"
#include "Cell_Culture/Population.h"

/**
 * @class
 * @brief Responsible for visually representing the simulation world on screen.
 * @details The class constructor is private. This is a singleton class that
 * visually represents the simulated world on the screen.
 */
class ScreenPrinter {

private:
    Terminal terminal;

    ScreenPrinter() {}

public:
    static ScreenPrinter& getInstance() {
        static ScreenPrinter instance;
        return instance;
    }

    /**
     * @brief Prints the population to screen
     * @param population the population that is to be printed
     * @test that a given population is printed as expected to the screen
     * @test that the parameter population isn't manipulated by the function.
     * It should be identical before and after the function is called.
     */
    void printBoard(Population& population);

    /**
     * @brief Prints help page to the screen
     */
    void printHelpScreen();

    /**
     * @brief Prints a message to the screen
     * @param message The message that is to be printed
     */
    void printMessage(string message);

    /**
     * @brief Clears the terminal
     */
    void clearScreen();
};

#endif
