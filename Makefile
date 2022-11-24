all:
	gcc -O3 llvm.c llvm-split-loop.c main.c -o benchmark

clean:
	rm benchmark

run: all
	time ./benchmark split
	time ./benchmark llvm

