#!/bin/bash

# File to read from and write to
input_file=$1
output_file=$2

# Process the file
awk '
/^Index/ {
    if (count >  0) {
        print word, count > "'"$output_file"'"
    }
    count=0
}
{
    count++
    if (/^Index/) {
        word=$4
    }
}
END {
    if (count >  0) {
        print word, count >> "'"$output_file"'"
    }
}
' "$input_file"
