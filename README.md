# Min Max k-Chinese Postman Problem (MMkCPP)

## Latest Release

You can download the lastest working executable from here: 

### Running the program: 

Example
```
./ga.exe ../benchmarks/gdb/gdb1.dat 2 1000 1000 5 3 0 1
```
Arguments
```
./ga.exe [graph file] [num robots] [pop size] [num gens] [num runs] [closed route vertex] [minimal output] [make visuals]
```
1. `[graph file]` the .csv or .dat graph. Must speficy the path to the file if not in same directory as ga.exe. Default is "../benchmarks/benchmarks/gdb/gdb1.dat"
2. `[seedFile]` the seed file
3. `[num robots]` the number of robots can be any number greater than or equal to 1 (k=...). Default is 1.
4. `[pop size]` number of individuals. Must be an even number. Default is 30.
5. `[num gens]` number of times to reproduce individuals. Can be any size. Default is 45.
6. `[closed route vertex]` starting and ending vertex for all robots. Use -1 for open routes. Default is -1.
7. `[minimal output]` can be 1 or 0. Will show you more or less information about the GA as it runs. Default is false.
8. `[make visuals]` can be 1 or 0. Will run the python visualizations after the GA is finished. Default is true.

## Getting Started for Development

### Dependencies

NOTE: These instructions are experimental and may not work

A list of dependencies that must be installed prior to code execution
 - Python3.X
   - Numpy
   - Scipy
   - MatPlot
 - Git Bash

#### Windows 10

1. Click in the Windows search bar and search for the application "Mircosoft Store"
2. Search in "Microsoft Store" for "Python 3.X" (any sub version of python 3 should work, I'm using 3.8)
3. Click on the Python App and Install it
4. Open "Powershell" and install the following Python packages
```
python3 -m pip install numpy
python3 -m pip install scipy
python3 -m pip install matplotlib
```

#### Linux

In terminal, install the following packages
```


```

### Compilation and Execution

#### Bash Script on Windows

1. Open Git Bash
2. Move to project directory with deploy.sh file
3. Run the following commands

```
chmod +x deploy.sh
./deploy.sh
```

#### Clion IDE using CMake

1. Open the project
2. Set the ToolChain to Microsoft Visual Studio
   - Click File
   - Click Settings
   - Click the tab "Build, Execution, Deployment"
   - Click the "Toolchains" tab
   - Type the Name "Visual Studio"
   - Set the environment to your version of Visual Studio (mine is C:\Program Files (x86)\Microsoft Visual Studio\2017\Community)
3. Right click src/CMakeLists.txt and select "Reload CMake Project"
   - To create the cmake-build-debug that clion recognizes
4. Use the green build hammer button to "build" or press the play button to "build and run".

#### Using GCC and Command Line Interface

```
cd src
g++ -o ga *.cpp -I. -lm
./ga
``` 

### Using CMake



## Relevant papers


### Benchmark Datasets
[Library of sample instances for the TSP in multiple formats.](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp/)  
[Capacitated Arc Routing Problems (CARP) and Vehicle Routing Problems](https://logistik.bwl.uni-mainz.de/forschung/benchmarks/)

## Documentation

### Full Cycle

## Meta
Working Environments: 
  - Windows 10 x32 x64
  - Ubuntu 18, 20
 
IDEs: 
[Jetbrains - Clion 2020](https://www.jetbrains.com/clion/)
[Visual Studio 2019](https://visualstudio.microsoft.com/)


Unity Version: 

## Contributors
Sushil Louis - https://github.com/sushillouis  
Bryan Dedeurwaerder - https://github.com/BryanDedeur  
Jonathan Peters - https://github.com/Jonathan-B-Peters  

## Advisor/s

Sushil Louis - https://github.com/sushillouis
