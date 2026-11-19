# Introduction to Run-Length Encoding (RLE): My Experience

Run-length encoding (RLE), a simple method for compressing data, is the subject of this project for COMP 211 at the University of North Carolina at Chapel Hill. The main topic is **data compression**, and specifically **run-length encoding (RLE)**.

## How does RLE work?

In simple terms, RLE takes a repeated sequence of characters and stores the character along with a count of how many times it repeats.

For example:

```
AAAABBBCCD -> 4A3B2C1D
```

Here, 10 characters have been reduced to 8.

## What did I explore?

I used an AI assistant to learn about RLE, then applied that knowledge by writing C code. Here are some things I investigated:

1. How does RLE work, and why?
2. When does RLE make data bigger instead of smaller?
3. How do you store RLE data in C using bytes?
4. Where are the likely bugs in my C code, such as buffer overflows?
5. How does RLE compare to **Huffman coding** and **LZ77**?

## Interesting findings

**1. RLE can double your data.**

"ABCD" becomes "1A1B1C1D". Each letter now has a count, so there are no savings. A normal English sentence (43 bytes) turned into 86 bytes.

**2. It works amazingly well on the right data.**

A small 40x10 text picture took up 400 bytes, and after RLE it took up only 28 bytes. One thousand zero bytes were reduced to just 8 bytes.

**3. The "4A3B" version is not what your computer actually stores.**

I assumed the encoded data would look like text digits, but it is really raw bytes: `04 41 03 42 02 43 01 44`. The `04` is the number four, not the character '4'. This connects to what we covered in COMP 211 about binary representation.

**4. A count byte only goes up to 255.**

A single run cannot be longer than the max value of a `uint8_t`, which is 255. For example, a run of 300 gets split into two parts: 255 and 45. That is why I test lengths of 254, 255, and 256.

**5. The decoder knows which byte is a count by position.**

Even-numbered positions are counts and odd-numbered positions are values. Because of this, a data byte that happens to look like a digit can never be mistaken for a count.

**6. There was a real bug in my decoder.**

When I first wrote the decoder, it simply trusted its input. If I gave it `FF 41` ("write 255 A's") but only had room for ten bytes of output, it wrote past the end of the buffer. **AddressSanitizer** caught this error. The fix was to pass the size of the output buffer into the function and check that there is enough space before writing. This is exactly what `rle_decode_safe` does.

**7. RLE cannot see patterns.**

"ABABABAB" has no runs, so all RLE can do is double it. Methods like LZ77 can spot patterns like this.

## Running the code

You need `gcc` and `make` installed.

```bash
cd code
make test     # runs the tests
make demo     # shows where RLE helps and hurts
make asan     # runs the tests under AddressSanitizer (memory checker)
make clean    # deletes the compiled programs
```

Expected output from `make demo`:

```
the picture above              400 ->    28 bytes  (7.0% of original)
1000 zero bytes               1000 ->     8 bytes  (0.8% of original)
a normal sentence               43 ->    86 bytes  (200.0% of original)
ABAB... pattern                 16 ->    32 bytes  (200.0% of original)
```

## What is inside this repository

| Folder / file | Description |
| --- | --- |
| `code/rle.c`, `code/rle.h` | The encoder and safe decoder |
| `code/test_rle.c` | Test cases, including edge cases (empty input, 255, 256, bad input) |
| `code/compression_demo.c` | Prints the compression numbers above |
| [`slides/`](slides/) | PowerPoint decks and speaking script |
| `resources.md` | Resources I used |
| `reflection.md` | How I used AI to study this |

## Ideas for next steps

- Stop non-repeating data from growing, like PackBits does with "literal" runs.
- Learn how Huffman coding builds its tree.
- Trace LZ77 by hand on "ABABABAB".
- Compare my RLE with `gzip` on the same files.

## Limitations of this project

My RLE only works one byte at a time and uses a fixed one-byte count. It is meant for learning, not for real use.
