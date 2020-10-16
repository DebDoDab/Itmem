#!/bin/bash
commands=$(ps -Ao "%u %p:%c")
commands=$(echo "$commands" | head -n -1)
tmp=$(echo "$commands" | grep -E "user.*" | awk '{print $2}')

if [[ -z "$tmp" ]]
then
    echo "0" > task1.log
else
    echo "$tmp" | wc -l > task1.log
    echo "$tmp" >> task1.log
fi
