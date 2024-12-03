#!/bin/bash

#./main < ./input/input.txt > ./output/output.txt

g++ -o gen gen.cpp
if [ $? -ne 0 ]; then
    echo "Error: Compilation of test.cpp failed on run #$i"
    exit 1
fi

./gen poj.txt 100 100 1 random out.txt
if [ $? -ne 0 ]; then
    echo "Error: test.cpp encountered a runtime error on run #$i"
    exit 1
fi