# Resources

## Things I read
- [Run-length encoding (Wikipedia)](https://en.wikipedia.org/wiki/Run-length_encoding)
- [PackBits (Wikipedia)](https://en.wikipedia.org/wiki/PackBits): a version of RLE that doesn't double non-repeating data
- [Huffman coding (Wikipedia)](https://en.wikipedia.org/wiki/Huffman_coding)
- [LZ77 and LZ78 (Wikipedia)](https://en.wikipedia.org/wiki/LZ77_and_LZ78)
- [DEFLATE spec, RFC 1951](https://datatracker.ietf.org/doc/html/rfc1951): the format gzip and PNG use (LZ77 + Huffman)

## Tools I used
- [AddressSanitizer docs](https://clang.llvm.org/docs/AddressSanitizer.html): for catching the buffer overflow in my first decoder
- AI assistant: explained concepts, wrote starter code, and checked my understanding. I tested the code myself instead of trusting it.

## COMP 211 ideas this connects to
- Binary representation and bytes
- Fixed-size integers like `uint8_t` (max 255)
- C strings and the null terminator
- Buffer overflows and memory safety
- Bitwise operations (these matter more for Huffman coding)
