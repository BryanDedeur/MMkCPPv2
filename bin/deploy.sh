#!/bin/bash

cd bin
graph_directory=$(ls ../benchmarks/arc-routing/*.csv)
ga_exe="./ga.exe"

for graph in $graph_directory; do
    "$ga_exe" "$graph" "30 2"
done

for graph in $graph_directory; do
    "$ga_exe" "$graph" "30 5"
done

for graph in $graph_directory; do
    "$ga_exe" "$graph" "30 1"
done

