#!/bin/bash

ga_exe="./ga.exe"

popSize=100
generations=200
closedRouteVertex=0
minimalOutput=1
makeVisuals=0
kValues=(1)
seedsFile="30seeds.txt"

# get the instances
for graph in instances/*; do
    for k in ${kValues[@]}; do
        $ga_exe $graph $seedsFile $k $popSize $generations $closedRouteVertex $minimalOutput $makeVisuals;
    done
done
