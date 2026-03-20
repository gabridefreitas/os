#!/bin/bash

# Example with variables

filename="/etc/passwd"
echo "Check for file permissions"
ls -l $filename
echo "Check how many accounts are in the system"
wc -l $filename