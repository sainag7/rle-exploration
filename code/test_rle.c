// test_rle.c
// Tests for rle.c. Run with: make test

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

// Encode then decode, and check we get the same thing back.
static void round_trip(const uint8_t *data, size_t n, const char *name) {
    uint8_t *enc = malloc(2 * n + 1);
    uint8_t *dec = malloc(n + 1);
    size_t enc_len = rle_encode(data, n, enc);
    size_t dec_len = rle_decode_safe(enc, enc_len, dec, n);
    assert(dec_len == n);
    assert(memcmp(data, dec, n) == 0);
    printf("PASS  %-22s %5zu bytes -> %5zu bytes\n", name, n, enc_len);
    free(enc);
    free(dec);
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

    // empty input
    round_trip((const uint8_t *) "", 0, "empty");

    // one character
    round_trip((const uint8_t *) "A", 1, "single char");

    // the example from my notes
    round_trip((const uint8_t *) "AAAABBBCCD", 10, "AAAABBBCCD");

    // no repeats at all (gets bigger!)
    round_trip((const uint8_t *) "ABCD", 4, "ABCD (no repeats)");

    // runs around the 255 limit
    int sizes[] = {254, 255, 256, 300, 1000};
    for (int s = 0; s < 5; s++) {
        size_t n = (size_t) sizes[s];
        uint8_t *buf = malloc(n);
        memset(buf, 'x', n);
        char name[32];
        snprintf(name, sizeof name, "%d x's", sizes[s]);
        round_trip(buf, n, name);
        free(buf);
    }

    // bad input: FF 41 means "write 255 A's" but we only have 10 bytes of room
    {
        uint8_t evil[2] = {0xFF, 0x41};
        uint8_t out[10];
        assert(rle_decode_safe(evil, 2, out, sizeof out) == (size_t) -1);
        printf("PASS  too-big count is rejected\n");
    }

    // bad input: odd length
    {
        uint8_t odd[3] = {1, 'a', 2};
        uint8_t out[10];
        assert(rle_decode_safe(odd, 3, out, sizeof out) == (size_t) -1);
        printf("PASS  odd-length input is rejected\n");
    }

    printf("\nAll tests passed.\n");
    return 0;
}
