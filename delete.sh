#!/bin/bash

echo "Searching for files ending with 'Zone.Identifier' to delete..."

# For each file found, echo its name and then delete it.
find . -type f -name "*Zone.Identifier" -exec echo "Deleting: {}" \; -exec rm {} \;

echo "File deletion process completed."