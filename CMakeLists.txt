cmake_minimum_required(VERSION 3.2)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

include_directories($ENV{TOOLS_INCLUDE} ${CMAKE_SOURCE_DIR}/include)

# Add terminal sub directory
add_subdirectory(terminal)

# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode
    message("Debug mode")
    add_definitions(-DDEBUG)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set(SRC_LIST
        src/main.cpp
        src/Cell_Culture/Cell.cpp
        src/Support/FileLoader.cpp
        src/GameOfLife.cpp
        src/Support/Globals.cpp
        src/Cell_Culture/Population.cpp
        src/GoL_Rules/RuleFactory.cpp
        src/GoL_Rules/RuleOfExistence.cpp
        src/ScreenPrinter.cpp
        src/GoL_Rules/RuleOfExistence_Conway.cpp
        src/GoL_Rules/RulesOfExistence_VonNeumann.cpp
        src/GoL_Rules/RuleOfExistence_Erik.cpp
        src/Support/MainArgumentsParser.cpp
        src/Support/MainArguments.cpp)

set(TEST_LIST
        test/main-test.cpp
        src/Cell_Culture/Cell.cpp
        src/Support/FileLoader.cpp
        src/GameOfLife.cpp
        src/Support/Globals.cpp
        src/Cell_Culture/Population.cpp
        src/GoL_Rules/RuleFactory.cpp
        src/GoL_Rules/RuleOfExistence.cpp
        src/ScreenPrinter.cpp
        src/GoL_Rules/RuleOfExistence_Conway.cpp
        src/GoL_Rules/RulesOfExistence_VonNeumann.cpp
        src/GoL_Rules/RuleOfExistence_Erik.cpp
        src/Support/MainArgumentsParser.cpp
        src/Support/MainArguments.cpp
        test/GameOfLife-Test.cpp)


add_executable(${PROJECT_NAME} ${SRC_LIST})

add_executable(${PROJECT_NAME}-Test ${TEST_LIST})

target_link_libraries(${PROJECT_NAME} Terminal)

target_link_libraries(${PROJECT_NAME}-Test Terminal)