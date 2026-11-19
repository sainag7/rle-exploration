// rle.c
// Simple run-length encoding (RLE) in C.
// Encoded data is a list of pairs: (count, value). Each is one byte.
// Example: "AAAB" becomes 03 41 01 42.

#include "rle.h"

// Encode. "out" needs room for 2 * n bytes (worst case).
// Returns how many bytes were written.
size_t rle_encode(const uint8_t *in, size_t n, uint8_t *out) {
    size_t o = 0;
    size_t i = 0;
    while (i < n) {
        uint8_t value = in[i];
        size_t run = 1;
        // count repeats, but stop at 255 because count is one byte
        while (i + run < n && in[i + run] == value && run < 255) {
            run++;
        }
        out[o++] = (uint8_t) run;
        out[o++] = value;
        i += run;
    }
    return o;
}
