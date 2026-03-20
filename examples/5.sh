#!/bin/bash

# With arguments

echo -e "First argument: $1"
echo -e "Third argument: $3"
echo -e "Last argument: ${!#}\n"

echo -e "Number of arguments: $#"
echo -e "List of arguments: $*"
echo -e "All arguments as separate words: $@\n"

# Shift arguments

echo -e "Shifting arguments...\n"

shift

echo -e "First argument: $1"
echo -e "Third argument: $3"
echo -e "Last argument: ${!#}\n"

echo -e "Number of arguments: $#"
echo -e "List of arguments: $*"
echo -e "All arguments as separate words: $@\n"

# Shift again

echo -e "Shifting arguments again...\n"

shift

echo -e "First argument: $1"
echo -e "Third argument: $3"
echo -e "Last argument: ${!#}\n"

echo -e "Number of arguments: $#"
echo -e "List of arguments: $*"
echo -e "All arguments as separate words: $@\n"