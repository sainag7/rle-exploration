# How I Applied AI to Understand RLE

## My start
An AI assistant explained how RLE works using what I know from COMP 211: C, binary, and bitwise operations. At first I figured RLE simply turned "AAAB" into "3A1B". Then I realized computers store raw byte values, which raised bigger questions about the 255 limit and about when RLE makes data bigger.

## Relevant prompts

1. *"I ran your code and want to double check it. Where could it have bugs, like buffer overflows or off-by-one errors with the null terminator? Show me the numbers for when RLE works well and when it doesn't."*

   I didn't just trust the code. This found a real bug in the decoder.

2. *"Here's my understanding in my own words: [my explanation]. Check it. What did I get right, what's wrong, and what should I add?"*

   This was the most helpful prompt. I had misunderstood how the data is stored, and the AI assistant cleared that up.

3. *"What are the limitations of RLE compared to Huffman coding or LZ77, and what should I ask next?"*

   This showed me how RLE fits into the bigger world of compression algorithms.

## How I used the responses
- When something was unclear, I asked for examples.
- Instead of assuming the code worked, I asked the AI assistant how it could fail.
- I wrote the concept in my own words and had the AI assistant check it.

## What I'd do differently
- Run and break the code myself before asking the AI to audit it.
- Ask for practice problems, like encoding a string by hand.
- Try the `gzip` comparison on real files.
