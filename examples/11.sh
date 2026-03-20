#!/bin/bash

# Functions

function hello {
    local name=$1
    echo "Hello, $name!"
    return 0
}

hello Gabriel