#!/bin/bash

METRICAS=("FLOPS_DP" "ENERGY")
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in "${METRICAS[@]}"
do
    likwid-perfctr -C ${CPU} -g $k -m ./ajustePol < $1 > ${k}.log
done

grep -e "Energy \[J\]" ENERGY.log
grep -e "AVX DP" FLOPS_DP.log

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
