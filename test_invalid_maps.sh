#!/bin/bash

MAP_DIR="maps/invalid"
EXECUTABLE="./cub3D"

echo "== Testing invalid maps in '$MAP_DIR' =="

for map in "$MAP_DIR"/*; do
	if [[ -f "$map" ]]; then
		echo "Testing $(basename "$map")..."
		
		# Exécute et capture la sortie d'erreur
		ERROR_OUTPUT=$($EXECUTABLE "$map" 2>&1)
		EXIT_CODE=$?

		if [ $EXIT_CODE -ne 0 ]; then
			echo "✅ Failed as expected (exit code $EXIT_CODE)"
			echo "Error output:"
			echo "$ERROR_OUTPUT"
		else
			echo "❌ Unexpected success (exit code $EXIT_CODE)"
		fi

		echo "----------------------------------------"
	fi
done