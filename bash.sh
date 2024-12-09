#!/bin/bash

# Define the executable and output file
EXECUTABLE="./main"
OUTPUT_FILE="output.txt"
TEMP_FILE="temp_output.txt"
MAX_ITERATIONS=10000  # Set the maximum number of iterations

# Run the program for the first time and save the output
$EXECUTABLE > $OUTPUT_FILE

# Loop for a specified number of times or until the output is different
for ((i=1; i<=MAX_ITERATIONS; i++)); do
    # Run the program and save the output to a temporary file
    $EXECUTABLE > $TEMP_FILE
    
    echo "Iteration $i"
    # Compare the current output with the last output
    if ! diff -q $OUTPUT_FILE $TEMP_FILE > /dev/null; then
        # If the output is different, break the loop
        break
    fi
    
    # If the output is the same, update the last output file
    mv $TEMP_FILE $OUTPUT_FILE
done

# Move the final different output to the output file if it exists
if [ -f $TEMP_FILE ]; then
    mv $TEMP_FILE $OUTPUT_FILE
    echo "Output has changed. Final output saved to $OUTPUT_FILE."
else
    echo "Output did not change after $MAX_ITERATIONS iterations."
fi