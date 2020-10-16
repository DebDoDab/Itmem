#!/bin/bash
tmp=$(ps -Ao "%u %p:%c" | grep -E "^$USER.*" | awk '{print $2}')

if [[ -z "$tmp" ]]
then
    echo "0" > task1.log
else
    echo "$tmp" | wc -l > task1.log
    echo "$tmp" >> task1.log
fi
