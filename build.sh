#! /bin/bash

find . -name build -prune -exec rm -r {} \;

if [[ $# -eq 0 ]]; then
    exit 1
elif [[ $1 == "clean" ]]; then
    exit 0
else
    cd $1
    mkdir build
    cmake -S . -B ./build
    cmake --build build
fi
