#!/bin/bash

for n in {15..22}
do
    if [[ -d AOC-20$n ]]
    then
        echo "Compiling solutions for Advent Of Code 20$n:"

        if ! [[ -d AOC-20$n/build ]]
        then
            mkdir AOC-20$n/build
        fi

        conan install -if AOC-20$n/build AOC-20$n --build=missing -s build_type=Release
        cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release -S AOC-20$n -B AOC-20$n/build
        cmake --build AOC-20$n/build -j8
    else
        echo "Solutions for AOC-20$n are not ready yet!"
    fi
done
