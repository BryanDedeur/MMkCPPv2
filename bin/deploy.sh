#!/bin/bash

cd bin
graph_directory=$(ls ../benchmarks/arc-routing/*.csv)
ga_exe="./ga.exe"

for graph in $graph_directory; do
    "$ga_exe" $graph 5 2 1000 1000
done

for graph in $graph_directory; do
    "$ga_exe" $graph 5 5 1000 1000
done

for graph in $graph_directory; do
    "$ga_exe" $graph 5 1 1000 1000
done

