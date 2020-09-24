#!/bin/bash

strlen() {
    require core.sh
    [[ "$#" -ne 1 ]] && print_error 1 "args count != 1"

    string="$1"
    echo ${#string}
}
