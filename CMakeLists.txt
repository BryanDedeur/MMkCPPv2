cmake_minimum_required(VERSION 3.12)

project(ga)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-I.")
SET(GCC_COVERAGE_LINK_FLAGS    "-lm")

# increase the memory size
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(ga 
        "src/main.cpp"
        
        "src/ga/GA.cpp"             "src/ga/GA.h"
        "src/ga/Population.cpp"     "src/ga/Population.h"
        "src/ga/Individual.cpp"     "src/ga/Individual.h"
                   

        "src/graph/Graph.cpp"       "src/graph/Graph.h"
        "src/graph/Path.cpp"        "src/graph/Path.h" 

        "src/Utils.cpp"             "src/Utils.h"
            
        "src/ga/Options.h"

  "src/graph/Edge.h" "src/graph/Edge.cpp"  "src/cpp/CPP.h" "src/cpp/CPP.cpp")