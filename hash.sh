#!/bin/bash

# Hashing and collision strategies
HASHING_STRATEGIES=("bad" "good")
COLLISION_STRATEGIES=("linear" "quadratic" "overflow")

# Directory for storing input and output files
INPUT_DIR="inputs"
OUTPUT_DIR="results"

# Create directories if they don't exist
mkdir -p $INPUT_DIR
mkdir -p $OUTPUT_DIR

# Generate input files using gen.txt
echo "Generating input files..."

g++ -o gen gen.cpp
./gen poj.txt 100 100 random "$INPUT_DIR/large_random.in"
./gen poj.txt 1 1 random "$INPUT_DIR/small_random.in"
./gen poj.txt 40 160 random "$INPUT_DIR/unequal_random.in"
./gen poj.txt 100 100 uniform "$INPUT_DIR/uniform.in"

echo "Input files generated."

# List of input datasets
DATA_SETS=("$INPUT_DIR/large_random.in" "$INPUT_DIR/small_random.in" "$INPUT_DIR/unequal_random.in" "$INPUT_DIR/uniform.in")

# Run tests and store output files
output_files=()  # Array to store output file names

echo "Running tests..."
for dataset in "${DATA_SETS[@]}"; do
    # Extract the dataset name without the path and extension
    dataset_name=$(basename "$dataset" .in)

    # Create a subdirectory for the dataset
    dataset_output_dir="$OUTPUT_DIR/$dataset_name"
    mkdir -p "$dataset_output_dir"

    output_files=()  # Array to store output files for this dataset

    for hashing in "${HASHING_STRATEGIES[@]}"; do
        for collision in "${COLLISION_STRATEGIES[@]}"; do
            # echo "Running test: Hashing=$hashing, Collision=$collision, Dataset=$dataset_name"
            
            # Generate a unique output filename within the dataset's directory
            output_file="$dataset_output_dir/${hashing}_${collision}.txt"
            output_files+=("$output_file")  # Add to the list of output files for this dataset
           
            # Execute the program and redirect output to the specific file
            ./main $hashing $collision < "$dataset" > "$output_file"
            
            # echo "Results stored in $output_file"
        done
    done

    # Compare output files for this dataset
    echo "Comparing output files for dataset $dataset_name..."
    base_file="${output_files[0]}"  # Use the first file as the baseline
    differences_found=0

    for file in "${output_files[@]:1}"; do
        if ! cmp -s "$base_file" "$file"; then
            echo "WARNING: Differences found between $base_file and $file"
            differences_found=1
        fi
    done

    if [[ $differences_found -eq 0 ]]; then
        echo "All output files for dataset $dataset_name are identical."
    else
        echo "Differences detected in output files for dataset $dataset_name. Check the warnings above."
    fi
done