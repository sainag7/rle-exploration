CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

.PHONY: all test asan clean

all: test_rle

test_rle: test_rle.c rle.c rle.h
	$(CC) $(CFLAGS) -o test_rle test_rle.c rle.c

test: test_rle
	./test_rle

# Same tests, but with AddressSanitizer to catch memory bugs
asan:
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o test_rle_asan test_rle.c rle.c
	./test_rle_asan

clean:
	rm -f test_rle test_rle_asan
