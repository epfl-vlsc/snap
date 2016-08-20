#!/usr/bin/env bash

set -eu

DIR=$(dirname "${BASH_SOURCE[0]}")
num_threads=$1
ref_index_path=/data/ref_index
input_path=/data/ERR174324_1.fastq.gz
output_path=/data/output.sam
flush_path=$DIR/../../tf-align/util/flush-cache.sh

prep_dir() {
    [ -e $output_path ] && rm $output_path
    make -C $DIR/..
    sudo $flush_path -p
    parallel "cat {} >/dev/null" ::: $ref_index_path/*
}

prep_dir

$DIR/../snap-aligner single $ref_index_path -t $num_threads -compressedFastq $input_path -o $output_path &
echo $! > pid && pidstat -hrdu -p `cat pid` 1 | sed '1d;/^[#]/{4,$d};/^[#]/s/^[#][ ]*//;/^$/d;s/^[ ]*//;s/[ ]\+/,/g' > pidstat_double_${num_threads}.csv && rm pid
