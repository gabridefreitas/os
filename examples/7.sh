#!/bin/bash

# Command composition

command1() {
    return 0
}

command2() {
    return 0
}

if command1; then
    echo "First command will be executed"
elif command2; then
    echo "Second command will be executed"
else
    echo "Third command will be executed"
fi 

echo "Continue with the rest of the script"

if [ -r README.md ]; then
    echo "README.md is readable"
fi

str1="Hello"
str2="World"

[[ "$str1" == str2 ]] && echo 1 || echo 0

[[ "$str1" != str2 ]]
echo $?

[[ "$str1" -eq "Hello" ]] && echo 1 || echo 0

[[ "$str1" -ne "Hello" ]]
echo $?

[[ "$str1" -ne "Hello" ]]
echo $?

[[ "$str1" -gt "Hello" ]]
echo $?

[[ "$str1" -ge "Hello" ]]
echo $?

[[ "$str1" -lt "Hello" ]]
echo $?

[[ "$str1" -le "Hello" ]]
echo $?

[[ ! "$str1" ]]
echo $?

case "$str1" in
    "Hello" | "Hi")
        echo "String is Hello"
        ;;
    "World")
        echo "String is World"
        ;;
    *)
        echo "String is something else"
        ;;
esac