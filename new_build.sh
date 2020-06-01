set -Eeuxo pipefail

if [ -x "$(command -v cmake3)" ]; then
    cmake_exec=$(command -v cmake3)
elif [ -x "$(command -v cmake)" ]; then
    cmake_exec=$(command -v cmake)
else
    echo "Could not find cmake executable"
    exit 1
fi

rm -r build/
mkdir build
cd build
${cmake_exec} ..
${cmake_exec} --build .
