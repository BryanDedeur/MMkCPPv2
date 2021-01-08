#!/bin/bash
# $1, the first argument is the name of the input file containing the graph
#
echo input file is $1
dir="D"
rm xa?
split -l 2 rx
i=0
for f in `ls xa?`
do
    mkdir $dir$i
    cp $f $dir$i
    echo copied $f to $dir$i
    cp $1 $dir$i
    echo copied $1 to $dir$i
    cp run.sh $dir$i
    echo copied run.sh to $dir$i    
    cp ../x64/Release/StacsGA.exe $dir$i
    echo "../x64/Release/StacsGA.exe to" $dir$i    
    ((i=i+1))
done
#
echo Done setting up, getting ready to run
#
echo "-----------"
#
j=0
until [ $j -gt 5 ]
do
    cd D$j
    ((j=j+1))
    rm outfile
    echo `pwd`
    source run.sh &
    cd ..
done

