CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

.PHONY: all test demo asan clean

all: test_rle compression_demo

test_rle: test_rle.c rle.c rle.h
	$(CC) $(CFLAGS) -o test_rle test_rle.c rle.c

compression_demo: compression_demo.c rle.c rle.h
	$(CC) $(CFLAGS) -o compression_demo compression_demo.c rle.c

test: test_rle
	./test_rle

demo: compression_demo
	./compression_demo

# Same tests, but with AddressSanitizer to catch memory bugs
asan:
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o test_rle_asan test_rle.c rle.c
	./test_rle_asan

clean:
	rm -f test_rle compression_demo test_rle_asan
