# ifndef VERBOSE
# .SILENT:
# endif

CC = g++

test :
	mkdir -p build
	$(CC) ./test.cpp -o ./build/test
	./build/test