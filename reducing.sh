#!/bin/bash

set -x
set -e

function get_size()
{
    r=0
    if [ -d $1 ]; then
        for f in $(find $1 -type f); do
            r=$(( $r + $(stat --format=%s $f) ))
        done
    fi
    echo $r
}

function get_count()
{
    r=0
    if [ -d $1 ]; then
        r=$(ls $1 | wc -l)
    fi
    echo $r
}

uniq_corpus_size=$(get_size corpus)
full_corpus_size=$(get_size corpus.tmp)

uniq_corpus_count=$(get_count corpus)
full_corpus_count=$(get_count corpus.tmp)

while [ $uniq_corpus_size -ne $full_corpus_size ] || [ $uniq_corpus_count -ne $full_corpus_count ]; do

    if [ 0 -eq $uniq_corpus_count ]; then
        echo "ERROR: Empty input corpus dir!"
        exit 1;
    fi

    rm -vrf corpus.tmp
    mkdir -vp corpus.tmp
    mv -vf corpus/* corpus.tmp/

    ./fuzz.py \
        -rss_limit_mb=6000 \
        -verbosity=1 \
        -merge=1 \
        -merge_control_file=merge_control_file.$(date +%s).txt \
        corpus/ \
        corpus.tmp/ \
        ;
 
    uniq_corpus_size=$(get_size corpus)
    full_corpus_size=$(get_size corpus.tmp)

    uniq_corpus_count=$(get_count corpus)
    full_corpus_count=$(get_count corpus.tmp)

    if [ 0 -eq $uniq_corpus_size ] || \
       [ 0 -eq $full_corpus_size ] || \
       [ 0 -eq $uniq_corpus_count ] || \
       [ 0 -eq $full_corpus_count ]; then
        echo "something went wrong"
        exit 1
    fi
    

    # research how it reduces
    exit 0




done

if [ $uniq_corpus_size -eq $full_corpus_size ] && [ $uniq_corpus_count -eq $full_corpus_count ]; then
    rm -vrf corpus.tmp
fi
