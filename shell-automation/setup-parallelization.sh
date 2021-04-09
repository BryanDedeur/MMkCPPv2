#!/bin/bash
# $1, the first argument is the name of the input file containing the graph

# environment parameters (you set these!)
executablePath="../build/ga.exe"
gaShellScript="run-ga.sh"
numCores=8
instancesDir="../problem-instances/bridge-generator2/"
seedsPath="../seed-files/3seeds.txt"

# make array of all the problem instances
instances=()
for file in $instancesDir/*; do
    instances=(${instances[@]} "$file")
done

# create directories for cores
echo "Staging a directory for each core"
numInstances=$(ls $instancesDir | wc -l)
numInstancesPerCore=$(($numInstances / $numCores))
numRemainingInstances=$(($numInstances - $(($numInstancesPerCore * $numCores)) ))
for i in $(seq 1 $numCores); do
    tempDir=parallelization/core$i
	rm -rf $tempDir
    mkdir $tempDir
    cp $executablePath $tempDir
    cp $seedsPath $tempDir
    cp $gaShellScript $tempDir
    mkdir $tempDir/instances 
    
    echo "core directory" $i": ready!"

    # copy num instances per core into the directory
    for j in $(seq 1 $numInstancesPerCore); do
        echo ${instances[$(($(( $(($i - 1)) * $numInstancesPerCore)) + $(($j - 1)) ))]}
        cp ${instances[$(($(( $(($i - 1)) * $numInstancesPerCore)) + $(($j - 1)) ))]} $tempDir/instances
    done

    # copy uneven problem instances into the directory
    if [ $(($i + $numCores * $numInstancesPerCore)) -le $numInstances ]; then
        echo ${instances[$(($i - 1 + $numCores * $numInstancesPerCore))]}
        cp ${instances[$(($i - 1 + $numCores * $numInstancesPerCore))]} $tempDir/instances
    fi

    #
done

# run executables
echo
echo "Running executables in parrallel"
for i in $(seq 1 $numCores); do
    tempDir=parallelization/core$i
    cd $tempDir
    source $gaShellScript &
    cd ../..
done