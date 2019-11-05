# ifndef VERBOSE
# .SILENT:
# endif

.PHONY = t

CC := gcc

TESTSRC := $(wildcard tests/*.c)
TESTS := $(TESTSRC:%.c=%)

default:
	mkdir -p ./build
	${CC} main.c -O2 -lpthread -o ./build/spellchecker ./headers/*.c
t: ${TESTS}

%: %.c
	mkdir -p ./build/tests
	${CC} $< -O2 -lpthread -o ./build/$@ ./headers/*.c
