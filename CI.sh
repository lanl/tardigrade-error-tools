#!/usr/bin/env bash

set -x

# Test dev branch against beta environment. All other branches against release
environment='release'
env_alias='sv3r'
if [ ${CI_MERGE_REQUEST_TARGET_BRANCH_NAME} == dev ]; then
    environment='beta'
    env_alias='sv3b'
fi

# Activate W-13 Python environment
source ./activate_w13pythonenv.sh ${env_alias} ${environment}

# Make bash script more like high-level languages.
set -Eeuxo pipefail

# report conda environment
conda info

# Clean and build project
./BUILD.sh

# Run project tests
./TEST.sh
