#!/bin/bash

FILEPATH="$(dirname -- "$(realpath "$0")")"

if [[ ! -f "$FILEPATH/core.sh" ]] || ! source "$FILEPATH/core.sh"; then
    echo "core.sh is dead :("
    exit 6  
fi

# Main part
[[ "$#" -eq 0 ]] && print_error 1 ":thinking:"

case "$1" in
    calc)
        require "$FILEPATH/modules/calc.sh"
        [[ "$#" -ne 4 ]] && print_error 1 "args count != 3"
        calc "$2" "$3" "$4"
        ;;
    search)
        require "$FILEPATH/modules/search.sh"
        [[ "$#" -ne 3 ]] && print_error 1 "args count != 2"
        search "$2" "$3"
        ;;
    reverse)
        require "$FILEPATH/modules/reverse.sh"
        [[ "$#" -ne 3 ]] && print_error 1 "args count != 2"
        reverse "$2" "$3"
        ;;
    strlen)
        require "$FILEPATH/modules/strlen.sh"
        [[ "$#" -ne 2 ]] && print_error 1 "args count != 1"
        strlen "$2"
        ;;
    log)
        require "$FILEPATH/modules/log.sh"
        [[ "$#" -ne 1 ]] && print_error 1 "args count != 0"
        log
        ;;
    exit)
        require "$FILEPATH/modules/exit.sh"
        [[ "$#" -gt 2 ]] && print_error 1 "args count > 1"
        exit_ ${1:-0}
        ;;
    help)
        require "$FILEPATH/modules/help.sh"
        help
        ;;
    interactive)
        require "$FILEPATH/modules/interactive.sh"
        [[ "$#" -ne 1 ]] && print_error 1 "args count != 0"
        interactive
        ;;
    *)
        require "$FILEPATH/modules/help.sh"
        help
        ;;
esac
