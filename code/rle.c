// rle.c
// Simple run-length encoding (RLE) in C.
// Encoded data is a list of pairs: (count, value). Each is one byte.
// Example: "AAAB" becomes 03 41 01 42.

#include <stdint.h>
#include <stdio.h>
#include <string.h>
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

// Safe decode. Checks that we never write past "out_cap".
// Returns bytes written, or (size_t) -1 if the input is bad.
size_t rle_decode_safe(const uint8_t *in, size_t n, uint8_t *out, size_t out_cap) {
    if (n % 2 != 0) return (size_t) -1;   // pairs only
    size_t o = 0;
    for (size_t i = 0; i < n; i += 2) {
        uint8_t count = in[i];
        if (count > out_cap - o) return (size_t) -1;  // would overflow
        memset(out + o, in[i + 1], count);
        o += count;
    }
    return o;
}
