#!/bin/bash

METRICAS=("L3" "L2CACHE" "FLOPS_DP")

grep 'L3 bandwidth' $1/log/L3.log > $1/dat/L3.dat
grep 'L2 miss ratio' $1/log/L2CACHE.log > $1/dat/L2CACHE.dat
grep 'Energy \[J\]' $1/log/ENERGY.log > $1/dat/ENERGY.dat
grep '  DP MFLOP\/s' $1/log/FLOPS_DP.log > $1/dat/FLOPS_DP.dat

for k in ${METRICAS[@]}
do
        grep "Tempo" $1/log/$k.log > $1/dat/TEMPO_$k.dat
done

