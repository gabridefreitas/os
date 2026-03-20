#!/bin/bash

# More variables examples

text="Testing..."

echo $text
echo "$text"
echo '$text'
echo `$text`

a_command=$(date)

echo $a_command
echo Today is $a_command
echo Today is \"the day\" to make some \$\$\$
echo 'Today is "the day" to make some $$$'
echo This is a\
    multi-line text
echo Current directory is $(pwd)