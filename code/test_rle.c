// Tests for rle.c. Run with: make test

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "rle.h"

static void check_encoding(const uint8_t *data, size_t n,
                           const uint8_t *expected, size_t expected_len) {
    uint8_t encoded[600];
    assert(n <= sizeof encoded / 2);
    size_t encoded_len = rle_encode(data, n, encoded);
    assert(encoded_len == expected_len);
    assert(memcmp(encoded, expected, expected_len) == 0);
}

int main(void) {
    uint8_t encoded[1] = {42};
    assert(rle_encode((const uint8_t *) "", 0, encoded) == 0);
    assert(encoded[0] == 42);
    puts("PASS  empty input writes nothing");

    const uint8_t single[] = {1, 'A'};
    check_encoding((const uint8_t *) "A", 1, single, sizeof single);
    puts("PASS  single byte encodes as one count/value pair");

    const uint8_t runs[] = {4, 'A', 3, 'B', 2, 'C', 1, 'D'};
    check_encoding((const uint8_t *) "AAAABBBCCD", 10, runs, sizeof runs);
    puts("PASS  repeated bytes encode as four pairs");

    const uint8_t no_repeats[] = {1, 'A', 1, 'B', 1, 'C', 1, 'D'};
    check_encoding((const uint8_t *) "ABCD", 4, no_repeats, sizeof no_repeats);
    puts("PASS  four distinct bytes expand to eight bytes");

    puts("All encoder tests passed.");
    return 0;
}
