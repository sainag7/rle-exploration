#ifndef RLE_H
#define RLE_H

#include <stddef.h>
#include <stdint.h>

size_t rle_encode(const uint8_t *in, size_t n, uint8_t *out);

#endif
