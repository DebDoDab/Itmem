#!/bin/bash

reverse() {
    require core.sh
    [[ "$#" -ne 2 ]] && print_error 1 "args count != 2"

    [[ -f "$1" ]] || print_error 3 "file $1 does not exists"

    [[ -r "$1" ]] || print_error 4 "file $1 is not readable"

    if [[ -e "$2" ]] && [[ ! -w "$2" ]] || [[ -d "$2" ]] || ! touch "$2" 2> /dev/null; then
        print_error 4 "file $2 is not writable"
    fi

    tmp="$(tac $1)" 2> /dev/null
    echo "$tmp" | rev > $2
    [[ "$?" -ne 0 ]] && print_error 5 "Something went wrong with rev"
}
