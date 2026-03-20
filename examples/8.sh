#!/bin/bash

# Conditional

echo "Find your command (who, list or cal)"

read i_command # Read user input

case "$i_command" in
    who | cal)
        echo "Executing $i_command"
        $i_command
        ;;
    list)
        echo "Executing ls..."
        ls
        ;;
    *)
        echo "Wrong command. Options are: who, list or cal"
        ;;
esac