/**
 * @file MainArgumentsParser.h
 * @author Andreas Lind
 * @author Mattias Lindell
 * @date 2017-10-28
 * @version 0.1
*/

#ifndef mainArgumentsParserH
#define mainArgumentsParserH

#include "MainArguments.h"
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * @class MainArgumentsParser
 * @brief parses and sets all the starting arguments for the application
*/

class MainArgumentsParser {
public:
    /**
     * @brief function parses all arguments provided by the user and sets the corresponding appValues
     * @param argv represents all arguments provided by the user
     * @param length represents nr of arguments
     * @return reference to ApplicationValues object
     * @test that appValues are set as expected
     */
    ApplicationValues& runParser(char* argv[], int length);

private:
    ApplicationValues appValues;

    /**
     * @brief Checks if a given option exists
     * @param begin represents starting point of list of provided arguments
     * @param end represents end point of list of provided arguments
     * @param option represents value to checked if it exists in provided arguments
     * @return true if parameter 'option' exists in provided arguments
     */
    bool optionExists(char** begin, char** end, const std::string& option);

    /**
     * @brief gets the given option value
     * @param begin represents starting point of list of provided arguments
     * @param end represents end point of list of provided arguments
     * @param option represents value to find in provided arguments
     * @return pointer to value to be set in appValues
     */
    char* getOption(char** begin, char** end, const std::string& option);
};

#endif
