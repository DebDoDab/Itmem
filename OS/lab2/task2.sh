#!/bin/bash
ps -Ao "%p %a" | grep -E "[[:space:]]+/sbin/" | awk '{print $1}' > task2.log
