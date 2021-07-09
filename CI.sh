#!/usr/bin/env bash

# Make bash script more like high-level languages.
set -Eeuxo pipefail

# report conda environment
conda info

# Clean and build project
./BUILD.sh

# Run project tests
./TEST.sh
