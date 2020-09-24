#!/bin/bash

log() {
    require core.sh
    [[ "$#" -ne 0 ]] && print_error 1 "args count != 0"
    
    file="/var/log/anaconda/X.log"
    [[ -f $file ]] || print_error 3 "file $file does not exists"

    warnings="$(cat $file | awk '{if(($3 == "(WW)") && ($1 == "["))print $0}')"
    info="$(cat $file | awk '{if(($3 == "(II)") && ($1 == "["))print $0}')"
    echo -e "${warnings//"(WW)"/"\e[33mWarning:\e[0m"}"
    echo -e "${info//"(II)"/"\e[94mInformation:\e[0m"}"
}
