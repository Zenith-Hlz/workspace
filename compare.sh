#!/bin/bash

# Set the number of iterations
read -p "Enter the number of times to run the script: " num_runs

for ((i=1; i<=num_runs; i++)); do
    echo "Run #$i"

    # Step 1: Run the Python file `gen.py` to generate input and store it in `./input/input.txt`
    python3 gen.py > ./input/input.txt
    if [ $? -ne 0 ]; then
        echo "Error: Failed to run gen.py on run #$i"
        exit 1
    fi

    # Step 2: Compile `test.cpp`
    g++ -o test test.cpp
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of test.cpp failed on run #$i"
        exit 1
    fi

    # Step 3: Run `test` using `./input/input.txt` and save output to `./output/output_main.txt`
    ./test < ./input/input.txt > ./output/output_test.txt
    if [ $? -ne 0 ]; then
        echo "Error: test.cpp encountered a runtime error on run #$i"
        exit 1
    fi

    # Step 4: Compile `main.cpp`
    g++ -o main main.cpp
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of main.cpp failed on run #$i"
        exit 1
    fi

    # Step 5: Run `main` using `./input/input.txt` and save output to `./output/output_main.txt`
    ./main < ./input/input.txt > ./output/output_main.txt
    if [ $? -ne 0 ]; then
        echo "Error: main.cpp encountered a runtime error on run #$i"
        exit 1
    fi

    # Step 6: Compare outputs
    if ! cmp -s ./output/output_test.txt ./output/output_main.txt; then
        echo "Error: Outputs are different on run #$i"
        exit 1
    fi

    echo "Success: Run #$i outputs are identical"
done

echo "All $num_runs runs completed successfully!"
