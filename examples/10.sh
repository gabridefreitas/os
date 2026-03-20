#!/bin/bash

# Loops

COUNTER=0

echo "While loop example:"

while [ "$COUNTER" -lt 10 ]; do
  echo "Current count: $COUNTER"
  # let COUNTER=COUNTER+1
  # ((COUNTER++))
  COUNTER=$((COUNTER + 1))
done

echo "For loop example:"

for COUNTER in $(seq 10); do
  echo "Current count: $COUNTER"
done

for i in $( ls ); do
  echo "File: $i"
done

for i in *; do
  echo "File: $i"
done