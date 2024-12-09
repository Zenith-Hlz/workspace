#!/bin/bash

# Set the number of iterations
read -p "Enter the number of times to run the script: " num_runs

for ((i=1; i<=num_runs; i++)); do
    echo "Run #$i"

    # Step 1: Compile and run the C++ file `gen.cpp` to generate input and store it in `./input/input.txt`
    g++ -o gen gen.cpp
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of gen.cpp failed on run #$i"
        exit 1
    fi

    ./gen > ./input/input.txt
    if [ $? -ne 0 ]; then
        echo "Error: Failed to run gen.cpp on run #$i"
        exit 1
    fi

    # Step 2: Compile and run `test.cpp` using `./input/input.txt` and save output to `./output/output_test.txt`
    g++ -o test test.cpp
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of test.cpp failed on run #$i"
        exit 1
    fi

    ./test < ./input/input.txt > ./output/output_test.txt
    if [ $? -ne 0 ]; then
        echo "Error: test.cpp encountered a runtime error on run #$i"
        exit 1
    fi

    # Step 3: Compile and run `main.cpp` using `./input/input.txt` and save output to `./output/output_main.txt`
    g++ -o main main.cpp
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of main.cpp failed on run #$i"
        exit 1
    fi

    ./main < ./input/input.txt > ./output/output_main.txt
    if [ $? -ne 0 ]; then
        echo "Error: main.cpp encountered a runtime error on run #$i"
        exit 1
    fi

    # Step 4: Compare outputs
    if ! cmp -s ./output/output_test.txt ./output/output_main.txt; then
        echo "Error: Outputs are different on run #$i"
        exit 1
    fi

    echo "Success: Run #$i outputs are identical"
done

echo "All $num_runs runs completed successfully!"
