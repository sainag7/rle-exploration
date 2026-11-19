// compression_demo.c
// Shows when RLE helps and when it hurts.
// Run with: make demo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

static void show(const char *name, const uint8_t *data, size_t n) {
    uint8_t *enc = malloc(2 * n + 1);
    size_t enc_len = rle_encode(data, n, enc);
    printf("%-28s %5zu -> %5zu bytes  (%.1f%% of original)\n",
           name, n, enc_len, 100.0 * (double) enc_len / (double) n);
    free(enc);
}

int main(void) {
    // 1. A tiny "picture": 40 wide, 10 tall. '.' is empty, '#' is filled.
    uint8_t pic[400];
    memset(pic, '.', sizeof pic);
    for (int row = 2; row <= 7; row++)          // a box
        memset(pic + row * 40 + 10, '#', 20);
    memset(pic + 9 * 40, '#', 40);              // a stripe on the last row

    printf("The picture:\n");
    for (int row = 0; row < 10; row++)
        printf("%.40s\n", (char *) pic + row * 40);
    printf("\n");

    show("the picture above", pic, sizeof pic);

    // 2. Lots of zeros
    uint8_t zeros[1000];
    memset(zeros, 0, sizeof zeros);
    show("1000 zero bytes", zeros, sizeof zeros);

    return 0;
}
