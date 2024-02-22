#!/bin/bash

res_dir=auto_tests/res
mkdir -p $res_dir

calculate_word_frequency() {
    src_file="$1"
    dest_file="$2"

    # Check if source file exists
    if [ ! -f "$src_file" ]; then
        echo "Source file does not exist."
        exit  1
    fi

    tr -d '[:punct:]' < $src_file | tr ' ' '\n' | sort | uniq -c | sort -k2,2 | awk '{print $2, $1}' > $dest_file
}

parse_output ()
{
    # input_file="$1"
    # output_file="$2"
    awk '
    /^Resultat/ { next } # Ignore lines starting with "Resultat"
    /^---/ { exit } # Stop processing when a line starts with "---"
    /^Index/ {
         if (count >  0) {
             print word, count
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
             print word, count
         }
     }
    ' - # < ./dico $input_file # | sort -k1 -o $output_file
    return 
}

for txt in ./exemples/*.txt; do 
    exp="exemples/expected/$(basename $txt)"
    if [[ ! -f $exp ]]; then
        calculate_word_frequency $txt $exp
    fi
    out=$res_dir/res_$(basename $txt)
    ./dico $txt | parse_output | sort -k1 -o $out
    diff -q $out $exp
    if [[ $? -ne 0 ]]; then
        echo "Test $txt failed"
    fi
done
