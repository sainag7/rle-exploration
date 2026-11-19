# Run-length encoding in C — speaking script

Use the bold words as rehearsal cues. The italic directions are places to point, pause, or advance. The times are approximate.

## 1 · Run-length encoding · 0:00

Hi, I’m Sai Nagamalla. For my project, I wanted to see when counting repeated letters actually saves space. Look at the first four A’s. If I were reading those to you over the phone, I’d probably just say **“four A’s.”** You could write down exactly what I started with. Run-length encoding, or RLE, uses that idea. Read the whole line that way and you get four A’s, three B’s, two C’s, and one D.

## 2 · How the decoder reads a pair · 0:30

Here’s what “four A’s” looks like inside my C program. *Point to 04 41.* These are two bytes, written in hexadecimal. The first byte answers **“how many?”** Zero-four means four copies. The second answers **“of what?”** Forty-one in hex is the code for a capital A.

You can read the next pair the same way. Zero-three means three copies, and forty-two in hex stands for B. Because the count always comes first, the decoder knows what to do even if the character it’s copying happens to be a digit.

## 3 · Which string will RLE shrink? · 1:15

Take a look at these two strings. Both have four A’s and four B’s, so they start out exactly the same size. **Which one do you think will take fewer bytes after encoding?** Picture the pairs you’d write down.

*Give the room about eight seconds. Take a show of hands for the first string, the second, or a tie. Ask one person, “What did you count?” Then advance.*

## 4 · Same letters, different sizes · 1:45

The top string only needs **two pairs**. There’s one for all four A’s and one for all four B’s. At two bytes per pair, that’s four bytes total, half of what we started with.

Now read the alternating string. One A, one B, one A, one B. Every time the letter changes, we start over. We end up with eight pairs, or sixteen bytes. Just moving the letters around took us from cutting the size in half to doubling it.

## 5 · A picture made of dots and hashes · 2:20

I tried the same encoder on this little picture. It’s forty characters wide and ten rows tall, so it starts at four hundred bytes. *Trace a row through the middle of the box.* I can describe that whole row in three pieces: ten dots, twenty hashes, ten dots.

Now follow those last ten dots around to the next row. The program reads the picture as **one continuous stream**, so it keeps counting dots. Across the whole picture there are only fourteen runs. Fourteen pairs at two bytes each comes out to twenty-eight bytes.

## 6 · The sentence that doubled in size · 3:05

Then I tried this sentence. You can spot repetition right away. The word **“the” shows up twice**. But look at the letters next to each other. Every letter is different from its neighbor, and the spaces are spread out too. So all forty-three characters get their own count of one. The same code that shrank the picture turns this sentence into eighty-six bytes.

## 7 · When does one pair pay off? · 3:35

*Point across A, AA, and AAA.* One A grows from one byte to two. **Two A’s break even.** Three A’s save a byte. The pair costs the same each time, so a longer run gets more out of it.

There is a limit in my version. I used one byte for the count, and the largest number it can hold is 255. For three hundred x’s, the encoder counts the first 255, then writes another pair for the remaining forty-five. That’s four bytes for all three hundred.

## 8 · The bug my first tests missed · 4:15

My first test was pretty straightforward. I compressed some data, expanded it, and checked that I got the original back. That passed. The part I’d missed was that I already knew the original size, so I always gave the decoder enough room.

AddressSanitizer, a tool that checks memory use, caught the decoder writing past the space set aside for it. The fix was to tell the decoder how much room it has. Before it copies a run, it checks **“Will this whole run fit?”** If the answer is no, it returns an error.

## 9 · Three ways to spot a pattern · 4:55

Think back to **ABABABAB**. It looks repetitive to us. My encoder still doubled it because it only counts identical neighbors. LZ77 can use a different clue. Once it’s seen the first AB, it can refer back to those letters to produce the later copies.

Huffman coding asks another question: how often does each letter appear overall? A common letter can get a shorter code even if its occurrences are far apart. Which method helps depends on what kind of repetition the data contains.

## 10 · What changed my understanding · 5:30

At first I thought **“4A” was literally what my program wrote**. I explained it that way to an AI assistant, then went back and checked the bytes. Seeing zero-four followed by forty-one made it click. The four is a count the decoder can use.

If I kept working on this, I’d go back to the sentence that doubled. I’d try storing its nonrepeating letters together in a block and measure what happens. Thanks. What questions do you have?
