#!/bin/bash

ga_exe="./ga.exe"

graph_directory=$(ls ../benchmarks/benchmarks/gdb/*.dat)

popSize=1000
generations=500
closedRouteVertex=0
runs=30
minimalOutput=0
makeVisuals=0

for graph in $graph_directory; do
    for k in {2..10}; do
        $ga_exe $graph $k $popSize $generations $runs $closedRouteVertex $minimalOutput $makeVisuals;
    done
done
