# Dictionary

A crossword puzzle utility

## Build & Run

    $ make
    $ ./dictionary 

## Usage

Select `1.` from the menu to load a file into the dictionary. Use `/usr/share/dict/words` if you don't have a dictionary file.

    1. Load file
    2. Check spelling
    3. Check shrinkability
    4. Clear data
    5. Quit

     Enter choice: 1

     Enter filename: /usr/share/dict/words
       Total time: 0.92069

## Spellchecker

Select `2.` from the menu to enter spellcheck mode. This works great for crossword puzzles. Just enter a pattern, using `?` as the wildcard, and the dictionary will search for all matches.

    Enter a word or pattern. Use '?' for wilcard: ?ron

    Words found:
      iron
      tron

      Total time: 0.00029

## Shrinkability

Select `3.` from the menu to enter shrinkability mode. The shrinkability of a word shows of the smallest word that can be created by stripping off one letter at a time from either the front or back of a word, with each intermediary word being another valid English word or entry from the dictionary.

    Enter a word to check its shrinkability index: revolver

    "revolver" => "revolve"
    "revolve" => "evolve"
    "evolve"

    Shrinkability index: 6

     Total time: 0.000252

# License

Copyright &copy; 2010 Mark Sands

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.