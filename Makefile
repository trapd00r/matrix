CC := gcc
CC_FLAGS := -D_POSIX_C_SOURCE=199309L -ansi -pedantic
CC_LIBS := -lm

all: matrix

matrix:
	$(CC) $(CC_FLAGS) -o ./matrix ./matrix.c $(CC_LIBS)

clean:
	rm -f ./matrix

