# Min Max k-Chinese Postman Problem (MMkCPP)

A genetic algorithm that evenly distributes k number of robots closed or open routes accross any undirected graph. 

Here is an example of the results produced for a custom graph with 10 robots.

```
R0 5 1 8 2 9 3 5  
R1 5 0 7 1 5  
R2 5 1 2 5  
R3 5 0 1 5  
R4 5 0 4 5  
R5 5 1 7 0 5  
R6 5 3 5  
R7 5 2 3 5  
R8 5 3 10 4 6 0 5  
R9 5 4 3 5
```

![10 Robots distributed travel plans produced by the GA](img/10-robot-travel.png)

## Latest Release

You can download the lastest working executable from here: [Latest Release](https://github.com/BryanDedeur/MMkCPPv2/releases/tag/2.3.1)

### Running the program: 

Example
```
./ga.exe ../benchmarks/gdb/gdb1.dat ../seeds/seeds.txt 5 1000 500 -1 0 1
```
Arguments
```
./ga.exe [graph file] [seedFile] [num robots] [pop size] [num gens] [closed route vertex] [minimal output] [make visuals]
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

A list of optional dependencies for the visualization and automation components:
 - Python3.X (for visulization stuff)
   - Numpy
   - Scipy
   - MatPlot
 - Git Bash (for automation parrallelization shell stuff)

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
If you are using a python environment then you just need to be sure to install the same packages into that invironment.

### Automation and IDEs

#### Shell Automation 

Shell automation is used to run the GA on mutiple problems and multiple seeds in parrallel and compile all the results together. To use the automation on Windows follow the steps below.

1. Open Git Bash
2. Ajust the run-ga.sh file with the ga parameters you desire
2. Run the following commands

```
cd shell-automation
source setup-parallelization.sh
```

Setup parrallelization will clone the executable of the GA into a folder for each processer core and assign specific problems to each core. Then it will simotaneously run all the executables.

#### [suggested!] Visual Studio 2017/2019 IDE

I highly recommend developing/building/debuging from Visual Studio. In order to get this project working you may need to ensure you have the proper CMake and C++ packages for Visual Studio.

Use the Visual Studio Installer and click "Modify" on your perferred version of Visual Studio to add the following extensions:
- Desktop Development with C++
  - Installation Details
    - Keep Default Options Checked
    - Add C++ MFC for latest v142 build tools (x86 & x64)
    - Add C++/CLI support for v142 build tools
    - Add C++ Modules for v142 build tools
    - Add C++ Clang tools for Windows
    
Click Modify and wait until finished...

Then open the project folder in Visual Studio, generate the cmake cache, select the run option "ga.exe", then you are ready to develop!

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

### Benchmark Datasets

The links below have many benchmarks instances that are readable by the GA.

[Library of sample instances for the TSP in multiple formats.](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp/)  
[Capacitated Arc Routing Problems (CARP) and Vehicle Routing Problems](https://logistik.bwl.uni-mainz.de/forschung/benchmarks/)

## Extra Notes

See the graph visualizer repository to visualize the results produced by the GA.
- https://github.com/BryanDedeur/Unity-Graphizer

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
