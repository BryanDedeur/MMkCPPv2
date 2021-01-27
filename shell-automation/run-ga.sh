#!/bin/bash

ga_exe="./ga.exe"

popSize=10
generations=20
closedRouteVertex=0
minimalOutput=1
makeVisuals=0
kValues=(1 2 5)
seedsFile="seeds.txt"

# get the instances
for graph in instances/*; do
    for k in ${kValues[@]}; do
        $ga_exe $graph $seedsFile $k $popSize $generations $closedRouteVertex $minimalOutput $makeVisuals;
    done
done
