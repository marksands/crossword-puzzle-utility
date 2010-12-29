# Dictionary

A crossword puzzle utility

## Build & Run

You must have boost installed and your $BOOST_ROOT env set.

    $ make

## Usage

    Usage: dictionary [options]

    Options:
      -h [ --help ]                         display this help and exit
      -f [ --file ] arg (=/usr/share/dict/words)
                                            load dictionary file
      -s [ --spellcheck ] arg               search for PATTERN in dictionary
      -r [ --reduce ] arg                   display reducable words for PATTERN
      -d [ --debug ]                        enable debugging
      -v [ --version ]                      print version information and exit

## Spellchecker

Use the `-s PATTERN` or `--spellcheck=PATTERN` option to spellcheck a given word. This works great for crossword puzzles. Just enter a pattern, using `?` as the wildcard, and the dictionary will search for all matches.

    $ dictionary --spellcheck="han?y"

       Words found:
         handy
         hanky

## Reduce

Use the `-r PATTERN` or `--reduce=PATTERN` option to check a words shrinkability. The shrinkability of a word shows of the smallest word that can be created by stripping off one letter at a time from either the front or back of a word, with each intermediary word being another valid English word or entry from the dictionary.

    $ dictionary --reduce "handy"

       "handy" => "hand"
       "hand" => "han"
       "han" => "ha"
       "ha" => "h"
       "h"

       Shrinkability index: 1

# License

Copyright &copy; 2010 Mark Sands

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.