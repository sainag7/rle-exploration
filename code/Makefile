CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

.PHONY: all test clean

all: test_rle

test_rle: test_rle.c rle.c rle.h
	$(CC) $(CFLAGS) -o test_rle test_rle.c rle.c

test: test_rle
	./test_rle

clean:
	rm -f test_rle
