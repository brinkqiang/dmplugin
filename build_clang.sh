#!/bin/bash

rm -rf build
mkdir -p build
cd build

cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo -- -j$(nproc)

cd ..

# popd

# echo continue && read -n 1
