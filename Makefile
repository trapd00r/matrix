CC := gcc
CFLAGS := -pedantic -ansi -D_POSIX_C_SOURCE=199309L
CLIBS := -lm

all: matrix

matrix:
	$(CC) $(CFLAGS) -o ./bin/matrix ./src/matrix.c $(CLIBS)

install:
	cp -v ./bin/matrix /usr/local/bin

uninstall:
	rm -fv /usr/local/bin/matrix

clean:
	rm -fv ./bin/matrix

