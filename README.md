# YSKCompressedHashmapDict - CPE593

Authors: Yihang Yuan, Parveen Sabah, and Eugene Kozlakov. 
Private Repo for Compressed Hashmap Dictionary project - CPE 593.

This repo contains our work on the HashTrie project. All of our final submission files can be found at the "front" of the repo.

A breakdown on our submission files:
  1. [CPE593 HashTrie.pptx](https://github.com/EKozlakov/YSKCompressedHashmapDict/blob/main/CPE593%20HashTrie.pptx) is the name of our final project slide file and presentation.
  2. [HashTrie_YangParveenKozlakov_FinalReport.pdf](https://github.com/EKozlakov/YSKCompressedHashmapDict/blob/main/HashTrie_YangParveenKozlakov_FinalReport.pdf) is the PDF file for our final report.
  3. [YSKHT_complexity.cpp](https://github.com/EKozlakov/YSKCompressedHashmapDict/blob/main/YSKHT_complexity.cpp) is the code we used for benchmarking and determining optimization.*
  4. [YSKHT_HashmapTrie_integration.cc](https://github.com/EKozlakov/YSKCompressedHashmapDict/blob/main/YSK_HashmapTrie_integration.cc) is the code we used for testing funcitonality.*

**NOTE**: 
The .cpp files exhibit what could be described as *undefined behavior* in terms of functionality on OSes other than Windows 10.The .cpp seem to compile across all platforms, but seem to execute as intended only on Windows 10.
Please contact ekozlako@stevens.edu or reach out to me on my discord at eugenekozlakov\#6819. I will gladly demonstrate the code execution and would love to get to the bottom of this OS incompatibility. 

---

## Prompt

Link to project prompt: https://github.com/StevensDeptECE/CPE593/tree/master/projects/hashdict. Prompt can also be found below.

Compressed Hashmap Dictionary Project

For this project you will be using a dictionary of 213k words, and a bigger one of 466k words to test.

The goal is to store the dictionary compactly and load it as fast as possible (and of course to be able to look up words efficiently once loaded). While it should be possible to update the dictionary, it is of seconday importance how fast that is, as generally the dictionary will not change.

This project implements a single hashmap where the strings are stored using arithmetic encoding in base 28. This allows from 26 letters and two end symbols END1 and END2 allowing distinguishing between two categories of words. For example, the word "hello" could be written

h e l l o END1

and the word goodbye could be written

g o o d b y e END2

The individual letters should be stored using arithmetic encoding. We will consider only single case, and words will only be letters so there are 26 separate symbols to represent for English.

To encode the words using arithmetic encoding, considering that there are 28 unique symbols including the two end symbols, use base 28, encoding each letter as a number from 0 to 25, END1=26 and END2=27.

The resulting equation would be ((8 * 28 + 5) * 28 + 12) * 28 ... ending in 26 for the END1 token.

Read in the dictionary and count the number of elements that start with the letter a. There will be many. Therefore, break down into words starting with aa, ab, ac, etc. Stop breaking down when the number of words is less than k. While this should be programmable, let's consider the number to be 64. This should mean that you identify all words starting with a given prefix, create a hashmap big enough to fit it in the table, then move to the next prefix, build another hashmap.
