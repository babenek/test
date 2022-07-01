#!/bin/bash

set -x
set -e


python fuzz.py \
    -rss_limit_mb=6000 \
    -seed=$(date +%s) \
    -atheris_runs=$(( 1234567890 + $(ls corpus | wc -l) )) \
    -verbosity=1 \
    corpus/ \
    ;

# Multithreading with -fork=$(nproc) may be not efficient due overhead for merging
