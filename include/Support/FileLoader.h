/*
 * Filename    FileLoader.h
 * Author      Erik Ström
 * Date        October 2017
 * Version     0.1
*/

#ifndef FileLoaderH
#define FileLoaderH

#include <map>
#include "Cell_Culture/Cell.h"
#include "Globals.h"

using namespace std;

/*
Determines starting values for simulation, based on contents of specified file.

Reads startup values from specified file, containing values for WORLD_DIMENSIONS and cell Population.
Will create the corresponding cells.
*/
class FileLoader {

public:
    FileLoader() {}

    void loadPopulationFromFile(map<Point, Cell>& cells);

};

#endif
