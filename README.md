# Min Max k-Chinese Postman Problem (MMkCPP)

## Getting Started for Development

### Dependencies

A list of dependencies that must be installed prior to code execution
- Jsoncpp: https://github.com/open-source-parsers/jsoncpp
- MatPlotLib-cpp: https://github.com/lava/matplotlib-cpp

#### Windows

1. Download vcpkg
- In powershell we must use vcpkg and the integrate to get the necessary packages installed properly

- Download vcpkg using the GitHub repository interface https://github.com/Microsoft/vcpkg
```
git clone https://github.com/Microsoft/vcpkg.git
```
- At this point you should unzip and rename the containing folder to simply "vcpkg"

2. Create a "src" directory under C: drive or windows install location and move vcpkg to the newly created directory
3. Install vcpkg
```
cd /src/vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```
4. Install the necessary packages
```
./vcpkg install jsoncpp
./vcpkg install matplotlib-cpp
```
#### Linux

In terimal enter the following commands
```
sudo apt-get install libjsoncpp-dev
```

### Compilation and Execution

#### Using CMake from IDE

##### Clion

1. Open the project
2. Right click src/CMakeLists.txt and select "Reload CMake Project"
   - To create the cmake-build-debug that clion recognizes
3. Use the build hammer to "build" or press the play "button to build" and run.

#### Using Command Line Interface

```
cd src
g++ -o ga *.cpp -I. -lm -ljsoncpp
./ga
``` 

### Using GCC



### Using CMake



## Relevant papers


### Benchmark Datasets
[Library of sample instances for the TSP in multiple formats.](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp/)  
[Capacitated Arc Routing Problems (CARP) and Vehicle Routing Problems](https://logistik.bwl.uni-mainz.de/forschung/benchmarks/)

## Documentation

### File input/output

![File IO](/img/file-io.png)

## Meta
Working Environments: 
  - Windows 10 - for Unity development  
  - Ubuntu 20 - for CPP code use and genetic algorithms  
 
IDEs: Clion  
Unity Version: 

## Contributors

Bryan Dedeurwaerder - https://github.com/BryanDedeur  
Jonathan Peters - https://github.com/Jonathan-B-Peters  
Sushil Louis - https://github.com/sushillouis

## Advisor/s

Sushil Louis - https://github.com/sushillouis
