#!/bin/sh

set -e


if (( $# < 2 )); then
	echo "Usage: $0 src_dir out_dir"
   	exit 1
fi

mkdir -p "$2"
docker build . -t sim-builder
docker run --rm \
    -u 1000:1000 \
    -v "$(readlink -f $1):/tmp/src:ro" \
    -v "$(readlink -f $2):/tmp/build" \
    sim-builder:latest

