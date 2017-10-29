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
     * @test that if no even rule name has been set, default to conway
     * @test that if no odd rule name has been set, default to same as even rule name
     */
    ApplicationValues& runParser(char* argv[], int length);

private:
    ApplicationValues appValues;

    // Checks if a given option exists
    bool optionExists(char** begin, char** end, const std::string& option);
    
    // gets the given option value
    char* getOption(char** begin, char** end, const std::string& option);
};

#endif
