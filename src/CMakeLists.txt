cmake_minimum_required(VERSION 3.17)

project(main)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-I.")
SET(GCC_COVERAGE_LINK_FLAGS    "-lm -ljsoncpp")

if(WIN32)

    find_package(jsoncpp CONFIG REQUIRED)

    list(APPEND CMAKE_PREFIX_PATH "/src/vcpkg/packages/jsoncpp_x86-windows/share/jsoncpp")

    include_directories(/src/vcpkg/packages/jsoncpp_x86-windows/include/json)

    add_executable(main main.cpp
            GA.cpp GA.h
            Population.cpp Population.h
            Individual.cpp Individual.h
            Utils.cpp Utils.h
            Evaluate.cpp Evaluate.h
            Options.h
            Const.h
            Graph.cpp Graph.h)

    target_link_libraries(main PRIVATE jsoncpp_lib jsoncpp_object)

else(WIN32) # LINUX OR DIFFERENT OS

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP jsoncpp)
    link_libraries(${JSONCPP_LIBRARIES})

    add_executable(main main.cpp
            GA.cpp GA.h
            Population.cpp Population.h
            Individual.cpp Individual.h
            Utils.cpp Utils.h
            Evaluate.cpp Evaluate.h
            Options.h
            Const.h
            Graph.cpp Graph.h)

    target_link_libraries(main ${JSONCPP_LIBRARIES})

endif(WIN32)
