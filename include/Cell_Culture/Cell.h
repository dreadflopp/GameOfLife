/**
 * @file Cell.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date October 2017
 * @version 0.1
*/

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"


// Data structure holding colors to visualize the state of cells.
struct StateColors {
    COLOR LIVING, // Representing living cell
            DEAD, // Representing dead cell
            OLD,  // Representing old cell
            ELDER;// Representing very old cell
}	/* Initiate default values. */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

// Cell action. Determined by rule, and sent to cell for future change.
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };

/**
 * @class Cell
 * @brief Cells in the simulated world
 * @details Cells represents a certain combination of row and column of the simulated world.
 * Cells may be of two types; rim cells, those representing the outer limits of the world,
 * or non-rim cells. The first cell type are immutable, exempt from the game's rules, and
 * thus their values may not be changed. The latter type, however, may be changed and edited
 * in ways specified by the rules.
 */
class Cell {

private:
    struct CellDetails {	// encapsulate cell details
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    struct NextUpdate {		// encapsulate changes to next state
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;


    void incrementAge() { details.age++; }

    void killCell() { details.age = 0; }

    // Sets the character value of the cell, which will be printed to screen.
    void setCellValue(char value) { details.value = value; }

    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Constructor
     * @details Constructor that determines the cell's starting values.
     * @param isRimCell A rim cell represents the border of the simulated world. Default is false, the cell is not a rim cell.
     * @param action The action the cell will make in the next generation. Default value is DO_NOTHING.
     */
    Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief Check if cell is alive.
     * @return true if cell is alive, otherwise false.
     * @test that true is returned if and only if the cell is alive
     */
    bool isAlive();

    /**
     * @brief Set cell action.
     * @details Sets the cells next action to take in its coming update.
     * @param action
     * @test that the correct action is set, check with Cell::getNextGenerationAction()
     */
    void setNextGenerationAction(ACTION action);

    /**
     * @brief Updates cell state.
     * @details Updates the cell to its new state, based on stored update values.
     * @test that a cell is killed if action is KILL_CELL. A dead cell has age == 0.
     * @test that age is increased by 1 if action is IGNORE_CELL.
     * @test that a cell with the action GIVE_CELL_LIFE gets age == 1 if it is not a rim cell.
     * @test that a cell with the action GIVE_CELL_LIFE gets age == 0 if it is a rim cell.
     */
    void updateState();

    /**
     * @brief Check cell age.
     * @details The function determines the age of the cell.
     * @return the age of the cell.
     * @test that the cells age is returned
     */
    int getAge() { return details.age; }

    /**
     * @brief Check cell color.
     * @return the color of the cell.
     * @test that the cells color is returned, set colors with Cell::SetNextColor()
     */
    COLOR getColor() { return details.color; }

    /**
     * @brief Check if cell is rim cell.
     * @details Determines whether the cell is a rim cell, and thus should be immutable.
     * @return true if the cell is a rim cell, otherwise false
     * @test that true is returned if and only the cell is a rim cell
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief Set color of the cell
     * @details Sets the color the cell will have after its next update.
     * @param nextColor The color the cell will have.
     * @test that the correct color is applied after the next update
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }


    /**
     * @brief Check cell value.
     * @details The function determines the value of the cell. The value is how the cell is represented on the screen.
     * @return the value of the cell.
     * @test that the cell has the expected value. Set with and test Cell::setNextCellValue()
     */
    char getCellValue() { return details.value; }

    /**
     * @brief Set cell value.
     * @details Sets the next character value of the cell, which will be printed to screen.
     * @param value The value to be set.
     * @test the correct value is applied after next update.
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Set dead/alive state.
     * @details Sets whether the cell is alive/dead next generation.
     * @param isAliveNext true if the cell shall be alive, otherwise false.
     * @test that the function sets the struct nextUpdate's member willBeAlive correctly.
     * Use Cell::isAliveNext() to check that the member is set.
     */
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    /**
     * @brief Will the cell be dead or alive?
     * @details Will the cell be alive next generation?
     * @return true if the cell will be alive, otherwise false.
     * @test that expected value is returned, test alongside with Cell::setIsAliveNext.
     */
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    /**
     * @brief Gets the cells next action..
     * @return the next action the cell will make.
     * @test that the expected value of the struct member nextGenerationAction is returned,
     * test the function alongside cell::setNextGenerationAction()
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }

    /**
     * @brief Get the cells next color. Function added for help with testing
     * @return the color the cell will have in the next generation
     */
    COLOR getNextColor() { return nextUpdate.nextColor; }
    /**
     * @brief Get the cells next value. Function added for help with testing
     * @return the value the cell will have in the next generation
     */
    char getNextCellValue() { return nextUpdate.nextValue; }
};

#endif
