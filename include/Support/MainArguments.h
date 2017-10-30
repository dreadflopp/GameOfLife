/**
 * @file MainArguments.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date October 2017
 * @version 0.1
*/

#ifndef GAMEOFLIFE_MAINARGUMENTS_H
#define GAMEOFLIFE_MAINARGUMENTS_H

#include "Globals.h"
#include "ScreenPrinter.h"
#include <sstream>
#include <string>

using namespace std;

struct ApplicationValues {
    bool runSimulation = true;
    string evenRuleName, oddRuleName;
    int maxGenerations = 100;

};

/**
 * @class BaseArgument
 * @brief base class for all argument classes
 * @details This class allows the user to modify the settings of the simulation
 * by setting argument when running the program
 */
class BaseArgument {
protected:
    const string argValue;

    // inform the user that no value was provided for the argument
    void printNoValue();

public:
    /**
     * @brief Constructor
     * @details Initiates the class and any of the derived classes with the
     * given argument.
     * @param argValue The argument with which to initiate the class
     */
    BaseArgument(string argValue) : argValue(argValue) {}
    virtual ~BaseArgument() {}

    /**
     * This function doesn't have any implementation and will be implemented
     * in the derived classes
     * @param appValues
     * @param value
     */
    virtual void execute(ApplicationValues& appValues, char* value = nullptr) = 0;

    const string& getValue() { return argValue; }
};

// Help screen
/**
 * @class HelpArgument
 * @brief Prints the help page to the screen
 * @details This derived class prints out the help page to the screen if the argument -h is given
 */
class HelpArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argValue "-h"
     */
    HelpArgument() : BaseArgument("-h") {}
    ~HelpArgument() {}

    /**
     * @brief Prints the help page
     * @details Prints the help page and modifies the appValues struct,
     * setting the simulation not to run
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param value This value will not be used
     * @test that appValues.runSimulation == false after the functions has been executed
     */
    void execute(ApplicationValues& appValues, char* value);
};

/**
 * @class GenerationsArgument
 * @brief Sets the amount of generations to simulate
 */
class GenerationsArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argument "-g"
     */
    GenerationsArgument() : BaseArgument("-g") {}
    ~GenerationsArgument() {}

    /**
     * @brief Sets the number of generations to simulate
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param generations the number of generations to simulate. If this parameter is left out,
     * an error message will be shown and sets the simulation not to run.
     * @test that appValues.runSimulation == false if the parameter generations is not set.
     * @test appValues.maxgenerations == generations if generations is set.
     */
    void execute(ApplicationValues& appValues, char* generations);
};

/**
 * @class WorldsizeArgument
 * @brief Sets the world size
 */
class WorldsizeArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argument "-s"
     */
    WorldsizeArgument() : BaseArgument("-s") {}
    ~WorldsizeArgument() {}

    /**
     * @brief Sets the world size
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param dimensions the world dimensions in the form [n]x[n] where n is an integer
     * @test that appValues.runSimulation == false if the parameter dimensions is not set.
     * @test the WORLD_DIMENSIONS is set correctly if the function has been succesfully executed
     */
    void execute(ApplicationValues& appValues, char* dimensions);
};

/**
 * @class FileArgument
 * @brief Initiate population from file
 */
class FileArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argument "-f"
     */
    FileArgument() : BaseArgument("-f") {}
    ~FileArgument() {}

    /**
     * @brief Reads information from file
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param fileNameArg the filename from which to read population data
     * @test that appValues.runSimulation == false if the parameter fileNameArg is not set.
     * @test the global variable FileName == fileNameArg after the function has been executed
     */
    void execute(ApplicationValues& appValues, char* fileNameArg);
};

/**
 * @class EvenArgument
 * @brief Rule used for even generations
 */
class EvenRuleArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argument "-er"
     */
    EvenRuleArgument() : BaseArgument("-er") {}
    ~EvenRuleArgument() {}

    /**
     * @brief Set the name of the even rule
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param evenRule the name of the even rule
     * @test that appValues.runSimulation == false if the parameter evenRule is not set.
     * @test that appValues.evenRuleName == evenRule after the function has been executed
     */
    void execute(ApplicationValues& appValues, char* evenRule);
};

/**
 * @class OddArgument
 * @brief Rule used for odd generations
 */
class OddRuleArgument : public BaseArgument {
public:
    /**
     * @brief Constructor
     * @details Initiates the class with the argument "-er"
     */
    OddRuleArgument() : BaseArgument("-or") {}
    ~OddRuleArgument() {}

    /**
     * @brief Set the name of the odd rule
     * @param appValues The struct with the current appValues. Returned by reference.
     * @param oddRule the name of the odd rule
     * @test that appValues.runSimulation == false if the parameter oddRule is not set.
     * @test that appValues.oddRuleName == oddRule after the function has been executed
     */
    void execute(ApplicationValues& appValues, char* oddRule);
};

#endif //GAMEOFLIFE_MAINARGUMENTS_H
