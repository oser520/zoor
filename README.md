# *zoor*

My chess engine. The seed has been planted!

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

I use [Debian][4], and that's what I'm using as my develoment environment. Anything
I say about building or compiling is thus only applicable to an operating system
environment similar to mine; however, if you have a compliant C++11 compiler, and a
recent version of *make*, then you should be able to build the unit tests without too
much fiddling.

## Short Term Goals

* **Evaluation Logic** Neet to implement one or more stretegies that can be employed
to evaluate a chess position, and can be plugged into the search algorithms to select
a move.
* **Search Logic** Examples of algorithms:
  * [AlphaBeta](https://chessprogramming.wikispaces.com/Alpha-Beta)
  * [B*](https://chessprogramming.wikispaces.com/B%2A)
  * [Monte Carlo Search Tree](https://chessprogramming.wikispaces.com/Monte-Carlo+Tree+Search)
* **Player Logic**
* **Game Logic**

Once all of these pieces are in place, it will be possible to play against the
engine. At this point the engine might not be very good, but the goal is for it
to be able to play a complete game, following the most important rules of the game
(e.g. non-tournament rules), with the ability to make every legal move,
such as castling and *en passant*. The next step will be to take on some of the
long term goals, and make **zoor** a good chess engine, which means that it will be
able to beat good chess players and other chess engines.

## Long Term Goals

* Make engine portable.
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
[4]: https://www.debian.org/
