cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp
        GA.cpp GA.h
        Population.cpp Population.h
        Individual.cpp Individual.h
        Utils.cpp Utils.h
        Evaluate.cpp Evaluate.h
        Options.h
        Const.h
        Graph.cpp Graph.h)

# from the matplotlib-cpp documentation
#find_package(Python2 COMPONENTS Development NumPy)
#target_include_directories(src PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
#target_link_libraries(src Python2::Python Python2::NumPy)