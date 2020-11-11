# Min Max k-Chinese Postman Problem (MMkCPP)

## Getting Started for Development

### Dependencies

NOTE: These instructions are experimental and may not work

A list of dependencies that must be installed prior to code execution
 - Python3.X
   - Numpy
   - Scipy
   - MatPlot

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

#### Using CMake from IDE

##### Clion

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
4. Use the build hammer to "build" or press the play "button to build" and run.

#### Using GCC and Command Line Interface

```
cd src
g++ -o ga *.cpp -I. -lm -ljsoncpp
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
 
IDEs: [Jetbrains - Clion 2020](https://www.jetbrains.com/clion/)

Unity Version: 

## Contributors
Sushil Louis - https://github.com/sushillouis  
Bryan Dedeurwaerder - https://github.com/BryanDedeur  
Jonathan Peters - https://github.com/Jonathan-B-Peters  

## Advisor/s

Sushil Louis - https://github.com/sushillouis
