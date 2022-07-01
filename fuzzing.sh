#!/bin/bash

set -x
set -e

THISDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

python fuzz.py \
    -rss_limit_mb=6000 \
    -seed=${seed} \
    -atheris_runs=$(( 1024000 + $(ls corpus | wc -l) )) \
    -verbosity=1 \
    corpus/ \
    ;

# Multithreading with -fork=$(nproc) may be not efficient due overhead for merging
