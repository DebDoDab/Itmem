#!/bin/bash
> task4.log
pids=$(ps -Ao "%p" | tail -n +2)
for pid in $pids
do
    ppid=$(cat /proc/$pid/status 2>/dev/null | grep -E "^PPid:" | awk '{print $2}')
    [[ -z "$ppid" ]] && continue
    sum=$(cat /proc/$pid/sched | grep -E "sum_exec_runtime" | awk '{print $3}')
    nr=$(cat /proc/$pid/sched | grep -E "nr_switches" | awk '{print $3}')
    art=$(echo "scale=7;$sum/$nr" | bc)
    echo "ProcessId=$pid : Parent_ProcessID=$ppid : Average_Running_Time=$art" >> task4.log
done
tmp=$(cat task4.log | sort -t ':' -nk2.19)
echo "$tmp" > task4.log
