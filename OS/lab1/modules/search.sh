#!/bin/bash

search() {
    [[ "$#" -ne 2 ]] && print_error 1 "args count != 2"

    [[ -d "$1" ]] || print_error 2 "$1 is not a directory"

    grep -r "$2" "$1" 2> /dev/null
}
