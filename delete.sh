#!/bin/bash

echo "Searching for files ending with 'Zone.Identifier' to delete..."

find . -type f -name "*Zone.Identifier" -exec echo "Deleting: {}" \; -exec rm {} \;

echo "Searching for directories named 'input' and 'output' to delete..."

find . -type d \( -name "input" -o -name "output" \) -exec echo "Deleting directory: {}" \; -exec rm -r {} \;

echo "File and directory deletion process completed."