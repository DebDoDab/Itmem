#!/bin/bash
printf "%7s %7s\n" /proc top
mmem=-1
mpid=-1
pids=$(ps -Ao "%p" | tail -n +2)
for pid in $pids
do
	mem=$(cat /proc/$pid/status 2>/dev/null | grep "VmRSS:" | awk '{print $2}')
	if [[ "$mem" != "" ]]; then
		if (( $mmem < $mem )); then
			mmem=$mem
			mpid=$pid
        fi
    fi
done
printf "%7s %7s\n" $mpid $(top -bn 1 -o %MEM | sed '8!d' | awk '{print $1}')
