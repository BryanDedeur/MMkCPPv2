cmake_minimum_required(VERSION 3.17)

project(main)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    include_directories(/src/vcpkg/packages/jsoncpp_x86-windows/include/json)
endif (WIN32)

find_package(jsoncpp CONFIG REQUIRED)

add_executable(main main.cpp
        GA.cpp GA.h
        Population.cpp Population.h
        Individual.cpp Individual.h
        Utils.cpp Utils.h
        Evaluate.cpp Evaluate.h
        Options.h
        Const.h
        Graph.cpp Graph.h)

target_link_libraries(main PRIVATE jsoncpp_lib)

# from the matplotlib-cpp documentation
#find_package(Python2 COMPONENTS Development NumPy)
#target_include_directories(src PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
#target_link_libraries(src Python2::Python Python2::NumPy)