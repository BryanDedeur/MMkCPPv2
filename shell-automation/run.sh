#!/bin/bash
#
#
rm outfile
for r in `cat xa?`
do
    echo Running Stacs GA with RandomSeed $r
    time ./StacsGA.exe $r > /dev/null
done
echo All Done
#grep "  149"  outfile | awk '{sum += $5; sumsq += $5*$5} END {print sum/NR ", " sqrt(sumsq/NR - (sum/NR)**2)}'
