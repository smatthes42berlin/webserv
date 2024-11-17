#!/bin/bash

# Directory to process (current directory in this case)
directory="."

# Loop through all files starting with location_
for file in "$directory"/location_*; do
  # Check if the file exists to prevent errors in case there are no matching files
  if [[ -f "$file" ]]; then
    # Rename the file by replacing "location_" with "server_"
    mv "$file" "${file/location_/server_}"
    echo "Renamed: $file -> ${file/location_/server_}"
  fi
done