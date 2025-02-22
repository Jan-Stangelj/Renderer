# /bin/bash

cmake -S . -B build/ -G Ninja
cd build
ninja
./Renderer