#!/bin/bash

MAP_DIR="maps/invalid"
EXECUTABLE="./cub3d"

echo "== Testing invalid maps in '$MAP_DIR' =="

# Loop through all files in the directory
for map in "$MAP_DIR"/*; do
	if [[ -f "$map" ]]; then
		echo -n "Testing $(basename "$map")... "
		$EXECUTABLE "$map" > /dev/null 2>&1
		EXIT_CODE=$?

		if [ $EXIT_CODE -ne 0 ]; then
			echo "✅ Failed as expected (exit code $EXIT_CODE)"
		else
			echo "❌ Unexpected success (exit code $EXIT_CODE)"
		fi
	fi
done