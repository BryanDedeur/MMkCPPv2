cmake_minimum_required(VERSION 3.17)

project(main)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    include_directories(/src/vcpkg/packages/jsoncpp_x86-windows/include/json)
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP jsoncpp)
    link_libraries(${JSONCPP_LIBRARIES})
endif (WIN32)

SET(GCC_COVERAGE_COMPILE_FLAGS "-I.")
SET(GCC_COVERAGE_LINK_FLAGS    "-lm -ljsoncpp")

add_executable(main main.cpp
        GA.cpp GA.h
        Population.cpp Population.h
        Individual.cpp Individual.h
        Utils.cpp Utils.h
        Evaluate.cpp Evaluate.h
        Options.h
        Const.h
        Graph.cpp Graph.h)

if (WIN32)
    target_link_libraries(main PRIVATE jsoncpp_lib jsoncpp_object)
endif(WIN32)

if (LINUX)
    target_link_libraries(main ${JSONCPP_LIBRARIES})
endif (LINUX)