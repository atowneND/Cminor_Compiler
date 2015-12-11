#!/bin/bash

expected_results=(3,2,8,15)
for i in $(seq 0 3); do 
    echo $i:
    ./cminor -codegen good$i.cminor good$i.s
    gcc good$i.s -o good$i.out
    ./good$i.out
    echo $?
    echo ""
done
