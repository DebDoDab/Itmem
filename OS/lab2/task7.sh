#!/bin/bash
>bsleep.log
>asleep.log
>tmp
all_pid=$(ls /proc | grep -Eo "^[0-9]+$")

for pid in $all_pid
do
	echo $pid" "$(cat /proc/$pid/io 2>/dev/null | grep "read_bytes" | awk '{print $2}') >> bsleep.log
done

sleep 60s

for pid in $all_pid
do
	echo $pid" "$(cat /proc/$pid/io 2>/dev/null | grep "read_bytes" | awk '{print $2}') >> asleep.log
done
cat asleep.log | while read line
do
	pid_tmp=$(echo $line | awk '{print $1}')
	adata=$(echo $line | awk '{print $2}')
	bdata=$(cat bsleep.log | grep -E "$pid" | awk '{print $2}')
	if [[ $bdata == "" ]]; then continue; fi
	minus=$(echo "$adata-$bdata" | bc)
	command=$(ps -q $pid_tmp -o comm=)
	echo "$pid_tmp:$command:$minus" >> tmp
done
cat tmp | sort -t":" -nrk3 | head -3
rm tmp bsleep.log asleep.log

