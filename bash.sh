#!/bin/bash

# Default values for input and output files
input_file="input/input.txt"

# Override defaults if arguments are provided
if [ -n "$2" ]; then
    input_file="$2"
fi
if [ -n "$3" ]; then
    output_file="$3"
fi

# Execute based on the first argument
if [ "$1" == "main" ]; then
    # Execute the C++ program
    ./main < "$input_file" > output/output_main.txt
elif [ "$1" == "python" ]; then
    # Execute the Python script
    python3 test.py < "$input_file" > output/output_python.txt
else
    echo "Usage: $0 {main|python} [input_file]"
    exit 1
fi
