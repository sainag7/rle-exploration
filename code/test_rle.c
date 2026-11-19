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

    uint8_t repeated[300];
    memset(repeated, 'x', sizeof repeated);

    const uint8_t below_limit[] = {254, 'x'};
    check_encoding(repeated, 254, below_limit, sizeof below_limit);
    puts("PASS  254 repeated bytes fit in one pair");

    const uint8_t at_limit[] = {255, 'x'};
    check_encoding(repeated, 255, at_limit, sizeof at_limit);
    puts("PASS  255 repeated bytes fit in one pair");

    const uint8_t above_limit[] = {255, 'x', 1, 'x'};
    check_encoding(repeated, 256, above_limit, sizeof above_limit);
    puts("PASS  256 repeated bytes split into 255 and 1");

    const uint8_t long_run[] = {255, 'x', 45, 'x'};
    check_encoding(repeated, 300, long_run, sizeof long_run);
    puts("PASS  300 repeated bytes split into 255 and 45");

    puts("All encoder tests passed.");
    return 0;
}
