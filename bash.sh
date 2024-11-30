#!/bin/bash

./main < input/input.txt > output/output_main.txt
python3 test.py < input/input.txt > output/output_python.txt
