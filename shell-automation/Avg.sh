#!/bin/bash
# $1 is line number to grep for
rm outfile
i=0
until [ $i -gt 5 ]
do
    cat D$i/outfile >> outfile
    echo concatenated D$i/outfile
    ((i=i+1))
done
grep " $1"  outfile | awk '{sum += $5; sumsq += $5*$5} END {print sum/NR ", " sqrt(sumsq/NR - (sum/NR)**2)}'

