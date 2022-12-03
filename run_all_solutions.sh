#!/bin/bash

./compile_all_solutions.sh &> /dev/null

echo "# Solutions for Advent Of Code events"
echo ""

for n in {15..22}
do
    if [[ -d AOC-20$n ]]
    then
        echo "## Advent Of Code 20$n"
        echo ""

        for day in {1..25}
        do
            if [[ -d "AOC-20$n/Day$day-p1" ]] || [[ -d "AOC-20$n/Day$day-p2" ]]
            then 
                echo "* Day $(printf "%2d" $day)"
            fi
            for part in {1..2}
            do
                problem_folder="AOC-20$n/Day$day-p$part"
                if [[ -d "$problem_folder" ]] && [[ -f "$problem_folder/solution" ]]
                then
                    echo "  * Part $part: $(./$problem_folder/solution < ./$problem_folder/input.txt)"
                fi
            done
        done

        echo ""
    else
        echo "> Solutions for AOC-20$n are not ready yet!"
    fi
done
