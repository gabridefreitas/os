#!/bin/bash

# Conditional

if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
elif [ ! -e $1 ]; then
    echo "File $1 does not exist."
elif [ ! -x $1 ]; then
    echo "File $1 is not executable."
    echo -n "Updating permissions... "
    chmod +x $1
    echo "Done."
else
    echo "File is executable. Running $1..."
    ./$1
fi