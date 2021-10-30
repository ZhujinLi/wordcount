wordcount
=========

This project is my personal playground to try writing word count programs in different programming languages including
shell scripts. It originates from a question in my first job interview a couple of years ago, which I failed :(

The task is rather simple: given a directory, the program is to count the number of occurrences of each word that ever
occurs in text files in that directory, recursively. The overall objective is simplicity rather than efficiency or
robustness, so issues like delimiter rule and error handling can be ignored.

Typically, an implementation demonstrates the control flow, subroutines and built-in libraries of the language, thus can
be regarded as a strengthened "hello world". As far as I know, there is a larger project online called `Rosetta Code
<https://rosettacode.org/wiki/Rosetta_Code>`_ with similar goals.

The results are expected to be like this:

::

      2 brown
      2 dog
      2 fox
      1 hello
      2 jumps
      2 lazy
      2 over
      2 quick
      4 the
      1 world
