#!/bin/bash

ga_exe="python Andrew_Brook_CPP.py"

# get the instances
for graph in ../../problem-instances/bridge-generator2/*; do
	echo
	echo $ga_exe $graph
	time $ga_exe $graph
done