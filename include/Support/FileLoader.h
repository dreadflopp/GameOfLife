/**
 * @file FileLoader.h
 * @author Mattias Lindell
 * @author Andreas Lind
 * @date October 2017
 * @version 0.1
*/

#ifndef FileLoaderH
#define FileLoaderH

#include <map>
#include "Cell_Culture/Cell.h"
#include "Globals.h"

using namespace std;

/**
 * @class FileLoader
 * @brief Reads starting values from file
 * @details Determines starting values for simulation, based on contents of specified file.
 * Reads startup values from specified file containing values for WORLD_DIMENSIONS and cell Population.
 * Will create the corresponding cells.
*/
class FileLoader {

public:
    FileLoader() {}

    /**
     * @brief Reads starting values from file
     * @details Loads the given map with cells read from the file that's pointed to by The global variable fileName
     * @param cells is given as in-data and is populated with cells and returned by reference.
     * @throws throws an error if the file is not found
     * @test that an error is thrown if the file is missing and the file argument is set
     */
    void loadPopulationFromFile(map<Point, Cell>& cells);

};

#endif
