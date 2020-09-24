#!/bin/bash

if [[ ! -f "core.sh" ]] || ! source "core.sh"; then
    echo "core.sh is dead :("
    exit 6
fi

# Main part
[[ "$#" -eq 0 ]] && print_error 1 ":thinking:"

case "$1" in
    calc)
        require modules/calc.sh
        calc ${@:2}
        ;;
    search)
        require modules/search.sh
        search ${@:2}
        ;;
    reverse)
        require modules/reverse.sh
        reverse ${@:2}
        ;;
    strlen)
        require modules/strlen.sh
        strlen ${@:2}
        ;;
    log)
        require modules/log.sh
        log ${@:2}
        ;;
    exit)
        require modules/exit.sh
        exit_ ${@:2}
        ;;
    help)
        require modules/help.sh
        help ${@:2}
        ;;
    interactive)
        require modules/interactive.sh
        interactive ${@:2}
        ;;
    *)
        require modules/help.sh
        help ${@:2}
        ;;
esac
