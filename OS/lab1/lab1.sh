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
        calc ${@:2}
        ;;
    search)
        require "$FILEPATH/modules/search.sh"
        search ${@:2}
        ;;
    reverse)
        require "$FILEPATH/modules/reverse.sh"
        reverse ${@:2}
        ;;
    strlen)
        require "$FILEPATH/modules/strlen.sh"
        strlen ${@:2}
        ;;
    log)
        require "$FILEPATH/modules/log.sh"
        log ${@:2}
        ;;
    exit)
        require "$FILEPATH/modules/exit.sh"
        exit_ ${@:2}
        ;;
    help)
        require "$FILEPATH/modules/help.sh"
        help ${@:2}
        ;;
    interactive)
        require "$FILEPATH/modules/interactive.sh"
        interactive ${@:2}
        ;;
    *)
        require "$FILEPATH/modules/help.sh"
        help ${@:2}
        ;;
esac
