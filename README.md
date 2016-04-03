# *zoor*

My personal chess engine. The seed has been planted!

Still have plenty to code before this is a working chess engine, so I don't recommend
downloading this repo, at least not yet.

## Requirements

#### Hard Requirements

These are required to compile and build the engine. Currently, it is not possible to
build the engine, because the engine is still missing most pieces, but it is possible
to build the unit tests for most of the parts that I've implemented. If you'd like to
build the unit tests, then I recommend doing so in the *stable-test* branch.

* C++11 compiler
* [GNU make][1]

#### Soft Requirements

These are only necessary to run unit tests, but the engine does not depend on them.

* Unit Tests
  * [googletest][2]
  * [python][3]

## Developmnet Environment

I use [Debian][9], and that's what I'm using as my develoment environment. Anything
I say about building or compiling is thus only applicable to an operating system
environment similar to mine; however, if you have a compliant C++11 compiler, and a
recent version of *make*, then you should be able to build the unit tests without too
much fiddling.

## Short Term Goals

* [ ] ***Board Logic*** The board logic is for the most part complete, but I'm not
marking it as complete yet, because I need to verify that the logic is correct.
Verifying that the logic works entails writing unit tests to check that moves are
generated correctly, which means constructing `Board`s with specific positions --
many of them because move logic is complex. Instead of proceeding to write code
to manually construct these `Board`s, this is a natural stopping point to look
into chess-notation systems for computers, and thus use chess notation files
construct `Board`s. Therefore, add logic to use one of the following computer chess
notations:
  * ***Portable game notation*** (PGN) See [here][4] and [here][5].
  * ***Forsyth-Edwards notation*** (FEN) See [here][6] and [here][7]. My initial
    impression is that this might be the easiest to implement.
  * ***Extended position description*** (EPD) See [here][8].
* [ ] ***Search Logic***
* [ ] ***Evaluation Logic***
* [ ] ***Player Logic***
* [ ] ***Game Logic***

Once all of these pieces are in place, it will be possible to play against the
engine. At this point the engine might not be very good, but the goal is for it
to be able to play a complete game, following the most important rules of the game
(e.g. non-tournament rules), with the ability to make every legal move,
such as castling and *en passant*. The next step will be to take on some of the
long term goals, and make **zoor** a good chess engine, which means that it will be
able to beat good chess players and other chess engines.

## Long Term Goals

* Create chess games database, by either designing one from scratch or creating an
  interface for an SQL or NoSQL database.
  * games should be stored compactly
  * do fast queries for games
* Create beginning game chess database.
* Create end game chess database.
* Use machine learning techniques to train evaluation functions.
* Explore GUI options.
  * What are good open source chess engine GUIs?
  * What would it take to create one from scratch?
* Investigate chess engine standards.
  * What are other chess engines doing that **zoor** should do?

[1]: https://www.gnu.org/software/make/
[2]: https://github.com/google/googletest
[3]: https://www.python.org/
[4]: https://en.wikipedia.org/wiki/Portable_Game_Notation
[5]: https://chessprogramming.wikispaces.com/Portable+Game+Notation
[6]: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
[7]: https://chessprogramming.wikispaces.com/Forsyth-Edwards+Notation
[8]: https://chessprogramming.wikispaces.com/Extended+Position+Description
[9]: https://www.debian.org/
