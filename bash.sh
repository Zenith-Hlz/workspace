#!/bin/bash

g++ -o test test.cpp
./test < input/input.txt > test.txt
g++ -o main main.cpp
./main < input/input.txt