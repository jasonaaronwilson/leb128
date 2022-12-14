all:
	gcc -O3 llvm.c llvm-split-loop.c array_notation.c parallel.c main.c -o benchmark
	clang -O3 llvm.c llvm-split-loop.c array_notation.c parallel.c main.c -o benchmark-clang

assembly-gcc:
	gcc -O3 -S llvm-split-loop.c

assembly-clang:
	clang -O3 -S llvm-split-loop.c

clean:
	rm -f benchmark benchmark-clang *~ llvm-split-loop.s

run: all
	time ./benchmark parallel
	time ./benchmark split
	time ./benchmark llvm
	time ./benchmark array
	time ./benchmark-clang split
	time ./benchmark-clang llvm
	time ./benchmark-clang array

