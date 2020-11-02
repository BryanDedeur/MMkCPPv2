cmake_minimum_required(VERSION 3.17)

project(ga)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-I.")
SET(GCC_COVERAGE_LINK_FLAGS    "-lm")

add_executable(ga src/main.cpp
        src/GA.cpp src/GA.h
        src/Population.cpp src/Population.h
        src/Individual.cpp src/Individual.h
        src/Utils.cpp src/Utils.h
        src/Evaluate.cpp src/Evaluate.h
        src/Options.h
        src/Const.h
        src/Graph.cpp src/Graph.h
        )
