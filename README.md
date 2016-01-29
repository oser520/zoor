# *zoor*

My personal chess engine. The seed has been planted!

Still have plenty to code before this is a working chess engine, so I don't recommend
downloading this repo, at least not yet.

## Requirements

### Hard Requirements

* C++11 compiler
* [GNU make](https://www.gnu.org/software/make/)

These are required to compile and build the engine.

### Soft Requirements

* Unit Tests
  * [googletest](https://github.com/google/googletest)
  * [python](https://www.python.org/)

These are only necessary to run unit tests, but the engine does not depend on them.

## Short Term Goals

* [ ] board class
* [ ] search logic
* [ ] evaluation logic

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
