#!/usr/bin/env bash

# Source the Intel compilers
source /apps/intel2016/bin/ifortvars.sh -arch intel64 -platform linux

# Make bash script more like high-level languages.
set -Eeuxo pipefail

# Clone and update dependencies
source update_dependencies.sh

# Find cmake3 executable
if [ -x "$(command -v cmake3)" ]; then
    cmake_exec=$(command -v cmake3)
elif [ -x "$(command -v cmake)" ]; then
    cmake_exec=$(command -v cmake)
else
    echo "Could not find cmake executable"
    exit 1
fi

# Clean and build repo tests
rm -rf build/
mkdir build
cd build
${cmake_exec} ..
${cmake_exec} --build ${tests}

# Perform repo tests
cd "${tests}"
./test_${repo}

# Check for failed tests
if grep -i false results.tex; then
    exit 1
fi
