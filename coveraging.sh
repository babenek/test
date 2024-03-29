#!/bin/bash

set -x
set -e

export SKIP_ATHERIS_INSTRUMENT=1

python -m coverage run \
    --source=. \
    fuzz.py \
    -rss_limit_mb=2048 \
    -atheris_runs=$(( 1 + $(ls corpus | wc -l) )) \
    -verbosity=1 \
    corpus/ \
    ;

# make html report
python -m coverage html
# remove uniq data to compare reports
(cd htmlcov && for f in $(ls . | grep '.*\.html'); do sed -i "s/.*created at.*//g" $f; done)

# report in text format
python -m coverage report
