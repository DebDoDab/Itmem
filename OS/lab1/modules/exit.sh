#!/bin/bash

exit_() {
    require core.sh
    [[ "$#" -gt 1 ]] && print_error 1 "args count > 1"

    
    [[ "$#" -ne 0 ]] && ! is_int $1 && print_error 2 "$1 is not an int"
    exit "${1:-0}"
}
