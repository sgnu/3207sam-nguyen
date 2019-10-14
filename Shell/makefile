# ifndef VERBOSE
# .SILENT:
# endif

CC = g++

default :
	mkdir -p build
	$(CC) ./main.cpp -o ./build/myshell
	./build/myshell

test :
	mkdir -p build
	$(CC) ./test.cpp -o ./build/test
	./build/test


clean :
	rm -rf build