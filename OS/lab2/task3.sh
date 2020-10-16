#!/bin/bash
commands=$(ps -Ao pid,start_time,command --sort=start_time)
commands=$(echo "$commands" | head -n -2)
echo "$commands" | tail -n 1 | awk '{print $1}'
