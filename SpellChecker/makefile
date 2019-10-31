# ifndef VERBOSE
# .SILENT:
# endif

.PHONY = t

CC := gcc

TESTSRC := $(wildcard tests/*.c)
TESTS := $(TESTSRC:%.c=%)

t: ${TESTS}

%: %.c
	mkdir -p ./build/tests
	${CC} $< -O2 -lpthread -o ./build/$@ ./headers/*.c