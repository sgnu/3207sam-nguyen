# ifndef VERBOSE
# .SILENT:
# endif

.PHONY = t

CC := gcc

TESTSRC := $(wildcard tests/*.c)
TESTS := $(TESTSRC:%.c=%)

library:
	${CC} -O2 -c ./csapp.c -o csapp.o

t: ${TESTS}

%: %.c
	mkdir -p ./build/tests
	${CC} $< -O2 -lpthread -o ./build/$@ csapp.o