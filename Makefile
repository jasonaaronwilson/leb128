all:
	gcc -O3 llvm.c main.c -o benchmark

run:
	time ./benchmark
