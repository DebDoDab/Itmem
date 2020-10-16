#!/bin/bash
>bsleep.log
>asleep.log
all_pid=$(ps -Ao "%p" | tail -n +2)

for pid in $all_pid
do
	echo $pid" "$(cat /proc/$pid/io 2>/dev/null | grep "read_bytes" | awk '{print $2}') >> bsleep.log
done

sleep 60s

for pid in $all_pid
do
	echo $pid" "$(cat /proc/$pid/io 2>/dev/null | grep "read_bytes" | awk '{print $2}') >> asleep.log
done

>tmp
while read line
do
	pid_tmp=$(echo $line | awk '{print $1}')
	adata=$(echo $line | awk '{print $2}')
	bdata=$(cat bsleep.log | grep -E "$pid" | awk '{print $2}')
	[[ -z $bdata ]] && continue
	diff=$(echo "$adata-$bdata" | bc)
	command=$(ps -q $pid_tmp -o comm=)
	echo "$pid_tmp:$command:$diff" >> tmp
done < asleep.log

cat tmp | sort -t ":" -nrk3 | head -3
rm tmp bsleep.log asleep.log

