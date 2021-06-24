#!/usr/bin/env bash

set -x
# Override default permissions. Set group to rx with no write permissions.
umask 0022

date
script=`basename "$0"`
echo "Running ${script}"

# Parse branch basename from expected path-like name, e.g. origin/branch.
branch=$(basename ${GIT_BRANCH})

# Deploy master branch against release environment. All other branches against beta.
if [ ${branch} == master ]; then
    environment='release'
    env_alias='sv3r'
    master=true
elif [ ${branch} == dev ]; then
    environment='beta'
    env_alias='sv3b'
    master=false
else
    echo "Unexpected branch name. Exiting..."
    exit 1
fi

# Activate W-13 Python environment
case $(hostname) in
    sstelmo.lanl.gov|mayhem.lanl.gov)
        projects="/projects"
        module load python/2020.07-python-3.8
        ${env_alias}
        ;;  # No fall through
    sn-fey?.lanl.gov|sn-rfe?.lanl.gov|sn???.lanl.gov)
        projects="/usr/projects/ea"
        module load python/3.8-anaconda-2020.07
        source activate /usr/projects/ea/python/${environment}
        module load intel
        ;;
    *)
        echo "Unknown or unsupported host $(hostname)."
        exit 2
esac

# Can treat bash like a scripting language after conda activation
set -Eeuxo pipefail

# For master branch, update tags before building documentation and whl
if ${master}; then
    # Run a fresh configuration to get VERSION file from GetVersionFromGit.cmake
    rm -rf build
    mkdir build
    cd build
    cmake ..
    cd ..
    # GetVersionFromGit.cmake bumps micro/patch version. Retrieve next release from VERSION
    production_version=$(cut -f 1 -d '*' VERSION)
    # First capture group is the major.minor.micro numbers
    # Second capture group is everything following micro
    version_regex='\([0-9]\+\.[0-9]\+\.[0-9]\+\)\(.*\)'
    # Catch unexpected production version regex and exit with error if suffix is found
    suffix=$(echo ${production_version} | sed "s/${version_regex}/\2/g")
    if [ -n "${suffix}" ]; then
        echo "Could not resolve the production version from ${old_version}. Left with ${production_version} and ${suffix}."
        exit 3
    fi
    developer_version=${production_version}+dev
    # Tag production commit and previous developer commit. Continue if already tagged.
    git tag -a ${production_version} -m "production release ${production_version}" || true
    last_merge_hash=$(git log --pretty=format:"%H" --merges -n 2 | tail -n 1)  # Assume last merge was dev->master. Pick previous
    git tag -a ${developer_version} -m "developer release ${developer_version}" ${last_merge_hash} || true
    git push origin --tags
fi

# Build project
./BUILD.sh

# Install project into conda environment by expected whl name.
./INSTALL.sh

# TODO: deploy documentation
