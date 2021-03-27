#!/bin/bash

print_error() {
    # print error $2 and exit with code $1
    echo "$2" > /dev/stderr
    exit "$1"
}

require() {
    if [[ ! -f "$1" ]] || ! source "$1"; then
        print_error 6 "Can't open $1"
    fi
}

contains() {
    # check if element $1 contains in array ${@:2}
    arr=${@:2}
    el=$1
    for element in ${arr[@]}; do
        if [[ "$element" == "$el" ]]; then
            return 0
        fi
    done

    return -1
}

is_int() {
    # check if argument $1 is integer by using regex
    [[ "$1" =~ ^[-+]?([1-9][0-9]*|0)$ ]] && return 0 || return -1
}


