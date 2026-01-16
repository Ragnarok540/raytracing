set -xe

mkdir -p bin

clang -Wall -Wextra -o bin/ppm src/ppm.c -lm
clang -Wall -Wextra -o bin/main src/main.c -lm
