# Make bash script more like high-level languages.
set -Eeuxo pipefail
cd "build"
cmake --install src/cpp --prefix /projects/python/beta
