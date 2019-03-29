#!/bin/bash

all_content="$(
for file in $(find ./testdata -type f); do
	cat $file
	echo
done
)"

echo "$all_content" | tr ' ' '\n' | sort | uniq -c
