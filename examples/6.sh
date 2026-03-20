#!/bin/bash

# Expressions

value=42

echo $((value = value - 8))
echo $((6 * 45 / 9))
echo $((value > 100))
echo $((value < 100))
echo $((value == 42))
echo $((value != 42))
echo $((value != 100))

B=2 D=2
A=$((B + 5 * (D / 3)))

echo $A
