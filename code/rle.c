// rle.c
// Simple run-length encoding (RLE) in C.
// Encoded data is a list of pairs: (count, value). Each is one byte.
// Example: "AAAB" becomes 03 41 01 42.

#include "rle.h"

// Encode. "out" needs room for 2 * n bytes (worst case).
// Returns bytes written, or (size_t) -1 if a run exceeds 255 bytes.
size_t rle_encode(const uint8_t *in, size_t n, uint8_t *out) {
    size_t o = 0;
    size_t i = 0;
    while (i < n) {
        uint8_t value = in[i];
        size_t run = 1;
        while (i + run < n && in[i + run] == value) {
            run++;
        }
        if (run > UINT8_MAX) {
            return (size_t) -1;
        }
        out[o++] = (uint8_t) run;
        out[o++] = value;
        i += run;
    }
    return o;
}
