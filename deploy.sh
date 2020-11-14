#!/bin/bash

graph_directory=$(ls benchmarks/arc-routing/*.csv)
ga_exe="./cmake-build-debug/ga.exe"

for graph in $graph_directory; do
    "$ga_exe" "$graph" "5 1"
done