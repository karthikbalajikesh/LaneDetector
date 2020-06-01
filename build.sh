#!/bin/bash

echo "Building Lane Detector"

cd build

rm -rf *

cmake .. -G "CodeBlocks - Unix Makefiles"

make
