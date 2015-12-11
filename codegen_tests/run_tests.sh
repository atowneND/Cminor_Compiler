#!/bin/bash

expected_results=(3,2,8,15,97,1,1)
for i in $(seq 0 6); do 
    echo $i:
    ./cminor -codegen good$i.cminor good$i.s
    gcc good$i.s -o good$i.out
    ./good$i.out
    echo $?
    echo ""
done
