#!/bin/bash

for n in {15..22}
do
    if [[ -d AOC-20$n ]]
    then
        echo "Cleaning solutions for Advent Of Code 20$n:"

        if [[ -d AOC-20$n/build ]]
        then
            cmake --build AOC-20$n/build --target clean

            rm -fr AOC-20$n/build
        fi
    else
        echo "Solutions for AOC-20$n are not ready yet!"
    fi
done
