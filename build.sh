#!/bin/bash

cd "$(dirname "$0")"

names=$(grep "^#ifdef NUM_DIGS" functions.cpp | awk '{print $2}' | sed 's/NUM_DIGS_//')

GCC=g++
CLANG=clang++

FLAGS="-g3 -O3 -static -Wall"

mkdir -p sanity
mkdir -p progs
mkdir -p simple

for t in ${names}; do
    D="NUM_DIGS_${t}"
    N=$(echo "${t}" | tr '[:upper:]' '[:lower:]' | tr '_' '-')

    ${GCC} ${FLAGS} benchmark.cpp -D"${D}"  -o "progs/${N}-gcc"
    if [ $(which "${CLANG}") ]; then
        ${CLANG} ${FLAGS} benchmark.cpp -D"${D}"  -o "progs/${N}-clang"
    fi

    ${GCC} ${FLAGS} simple.cpp -D"${D}" -DOP_XOR  -o "simple/${N}-xor"
    ${GCC} ${FLAGS} simple.cpp -D"${D}" -DOP_ADD  -o "simple/${N}-add"

    ${GCC} ${FLAGS} sanity.cpp -D"${D}"  -o "sanity/${N}"
done
