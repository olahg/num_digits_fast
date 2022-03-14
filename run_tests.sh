#!/bin/bash -xue

cd "$(dirname "$0")"

mkdir -p results

for dataset in data/data_*.txt; do
    for prog in progs/*; do
        result=$(basename "${dataset}")
        taskset 0x1 ./${prog} ${dataset} >> results/out_${result}
    done
done
