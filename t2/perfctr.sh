#!/bin/bash

VALORES_TESTE=(64 128 200, 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000)
#VALORES_TESTE=(64 128 200 256)
METRICAS=("FLOPS_DP" "L3" "L2CACHE")

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in ${METRICAS[@]}
do
        > $1/log/$k.log
        for n in ${VALORES_TESTE[@]}
        do
                likwid-perfctr -C 3 -g $k -m $1/./ajustePol < testes/$n.in  >> $1/log/$k.log
        done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
