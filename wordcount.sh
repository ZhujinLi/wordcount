#!/bin/bash

find ./testdata -type f -exec cat {} \; -exec echo \; |\
tr ' ' '\n' | sort | uniq -c
