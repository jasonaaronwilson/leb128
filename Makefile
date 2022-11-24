all:
	gcc -O3 llvm.c llvm-split-loop.c main.c -o benchmark
	clang -O3 llvm.c llvm-split-loop.c main.c -o benchmark-clang

clean:
	rm benchmark benchmark-clang *~

run: all
	time ./benchmark split
	time ./benchmark llvm
	time ./benchmark-clang split
	time ./benchmark-clang llvm

