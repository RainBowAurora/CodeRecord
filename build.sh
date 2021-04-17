#!/bin/bash

build_dir="build"

function print_usage(){
    local prog="$(basename $0)"
    echo "Usage:"
    echo "bash ${prog} [Options]"
    echo "Available options:"
    echo "-c, --clean     Clear workspace" 
    echo "-b, --build     Build all work"
    echo "-h, --help      Show this message and exit"
}

function delete_build(){
    if [ -d ${build_dir} ];then
        rm -rf ${build_dir}
    fi
}

function build_object(){
    delete_build
    mkdir ${build_dir} && cd ${build_dir}
    [ $? -eq 0 ]  && cmake .. || exit 2
    [ $? -eq 0 ]  && make || exit 2
    [ $? -eq 0 ]  && find -name "*_test" -type f | bash || exit 3
}

function parse_arguments() {
    if [[ $# -eq 0 ]] || [[ "$1" == "--help" ]]; then
        print_usage
        exit 0
    fi

    while [[ $# -gt 0 ]]; do
        local opt="$1"
        shift
        case $opt in
            -h|--help)
                print_usage
                exit 0
                ;;
            
            -b|--build)
                build_object
                exit 0
                ;;

            -c|--clear)
                delete_build
                exit 0
                ;;
            *)
                echo "Unknown option: ${opt}"
                print_usage
                exit 1
                ;;
        esac
    done
}


parse_arguments "$@"
