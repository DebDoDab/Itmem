#!/bin/bash
commands=$(ps -Ao "%p %a")
commands=$(echo "$commands" | head -n -1)
echo "$commands" | grep -E "[[:space:]]+/sbin/" | awk '{print $1}' > task2.log
