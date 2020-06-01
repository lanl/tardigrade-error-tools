set -Eeuxo pipefail

cmake_exec=$(which cmake3)
if [[ $? -ne 0 ]]; then
    cmake_exec=$(which cmake)
fi

rm -r build/
mkdir build
cd build
${cmake_exec} ..
${cmake_exec} --build .
