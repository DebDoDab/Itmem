#!/bin/bash

calc() {
    require core.sh

    # exits with code 1 if args count is not equal to 3
    [[ "$#" -ne 3 ]] && print_error 1 "args count != 3"
    
    ! is_int "$2" && print_error 2 "$1 is not an int"
    ! is_int "$3" && print_error 2 "$2 is not an int"

    case $1 in 
        sum)
            echo $(($2 + $3))
            ;;
        sub)
            echo $(($2 - $3))
            ;;
        mul)
            echo $(($2 * $3))
            ;;
        div)
            [[ "$3" -eq 0 ]] && print_error 2 "arg1 is 'div' but arg3 is 0"
            echo $(($2 / $3))
            ;;
        *)
            print_error 2 "$1 is not sum/sub/mul/div"
    esac
}
