#!/bin/bash
save() {
    avgart=$(echo "scale=7;$2/$3" | bc)
    echo "Average_Sleeping_Children_of_ParentID=$1 is $avgart" >> task5.log
}

> task5.log
ppid=-1
count=0
sumart=0

while read line
do
    curppid=$(echo "$line" | awk -F "[=:]" '{print $4}')
    curart=$(echo "$line" | awk -F "[=:]" '{print $6}')
    if (( $ppid != $curppid && $ppid != -1 )) ; then
        save $ppid $sumart $count
        count=0
        sumart=0
    fi
    ppid=$curppid
    sumart=$(echo "scale=7;$sumart+$curart" | bc)
    ((count++))
    echo "$line" >> task5.log
done < task4.log
save $ppid $sumart $count
