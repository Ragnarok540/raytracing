set -xe

mkdir -p bin

clang -Wall -Wextra -o bin/ppm src/ppm.c -lm
