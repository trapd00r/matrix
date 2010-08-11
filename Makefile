CC := gcc
CC_FLAGS := -D_POSIX_C_SOURCE=199309L -ansi -pedantic

all: matrix

matrix:
	$(CC) $(CC_FLAGS) -o ./matrix ./matrix.c

clean:
	rm -f ./matrix

