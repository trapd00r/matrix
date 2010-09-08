CC := gcc
CC_FLAGS := -pedantic -ansi -D_POSIX_C_SOURCE=199309L
CC_LIBS := -lm

all: matrix

matrix:
	$(CC) $(CC_FLAGS) -o ./bin/matrix ./src/matrix.c $(CC_LIBS)

install:
	cp -v ./bin/matrix /usr/local/bin

uninstall:
	rm -fv /usr/local/bin/matrix

clean:
	rm -fv ./bin/matrix

