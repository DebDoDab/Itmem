#!/bin/bash

interactive_calc() {
    # Enter 3 args
    require modules/calc.sh
    require core.sh

    operation=""
    possible_operations=("sum" "sub" "mul" "div")
    while [[ -z "$operation" ]] || ! contains $operation ${possible_operations[@]}; do
        if [[ -n "$operation" ]]; then
            echo "Wrong operation. Try again."
        fi
        read -p "Enter operation (sum/sub/mul/div): " operation
    done

    num1=""
    while [[ -z "$num1" ]] || ! is_int $num1; do
        if [[ -n "$num1" ]]; then
            echo "It's not int. Try again."
        fi
        read -p "Enter first number: " num1
    done


    num2=""
    while [[ -z "$num2" ]] || ! is_int $num2; do
        if [[ -n "$num2" ]]; then
            echo "It's not int. Try again."
        fi
        read -p "Enter second number: " num2
    done

    calc "$operation" "$num1" "$num2"
}

interactive_search() {
    # Enter 2 args
    require modules/search.sh

    dir=""
    while [[ -z "$dir" ]] || [[ ! -d "$dir" ]]; do
        if [[ -n "$dir" ]] && [[ ! -d "$dir" ]]; then
            echo "It's not a directory"
        fi
        read -p "Enter directory: " dir
    done

    regex=""
    while [[ -z "$regex" ]]; do
        read -p "Enter regular expression: " regex
    done

    search "$dir" "$regex"
}

interactive_reverse() {
    # Enter 2 args
    require modules/reverse.sh

    file1=""
    while [[ -z "$file1" ]] || [[ ! -e "$file1" ]]; do
        if [[ -n "$file1" ]] && [[ ! -e "$file1" ]]; then
            echo "This file doesn't exists"
        elif [[ -n "$file" ]] && [[ ! -r "$file1" ]]; then
            echo "Don't have permissions to read from that file"
        fi
        read -p "Enter first file: " file1
    done

    file2=""
    while [[ -z "$file2" ]]; do
        read -p "Enter second file: " file2
    done

    reverse "$file1" "$file2"
}

interactive_strlen() {
    # Enter 1 arg
    require modules/strlen.sh

    str=""
    while [[ -z "$str" ]]; do
        read -p "Enter string: " str
    done

    strlen "$str"
}

interactive_log() {
    # Enter 0 args
    require modules/log.sh

    log
}

interactive_exit() {
    # Enter 1 positional arg
    require modules/exit.sh

    exitcode=""
    read -p "Enter exit code or leave it empty: " exitcode

    exit_ "${exitcode:-0}"
}

interactive_help() {
    # Enter 0 args
    require modules/help.sh

    help
}

interactive() {
    require lab1.sh
    
    while [[ 1 -ne 2 ]]; do
        possible_actions=("calc" "search" "reverse" "strlen" "log" "exit" "help")
        
        for index in ${!possible_actions[@]}; do
            echo "$index. ${possible_actions[index]}"
        done

        option=""
        while [[ -z "$option" ]]; do
            read -p "Choose one action by typing its number or name: " option
        done

        if is_int "$option"; then
            if [[ "$option" =~ ^[0-6] ]]; then
                action=${possible_actions[$option]}
            else
                echo "Invalid command number. Try again"
                continue
            fi
        else
            if contains $option ${possible_actions[@]}; then
                action=$option
            else
                echo "Invalid command name. Try again"
                continue
            fi
        fi

        case $action in
            "calc")
                interactive_calc
                ;;
            "search")
                interactive_search
                ;;
            "reverse")
                interactive_reverse
                ;;
            "strlen")
                interactive_strlen
                ;;
            "log")
                interactive_log
                ;;
            "exit")
                interactive_exit
                ;;
            "help")
                interactive_help
                ;;
        esac


    done
}
