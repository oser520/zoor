# *zoor*

My personal chess engine. The seed has been planted.

Still have plenty to code before this is a working chess engine, so I don't recommend
downloading this repo, at least not yet. I'm currently working on the class that
represents the board, which also handles the logic for piece moves.

Todo list (short term goals):\
[ ] finish board class \
[ ] implement search logic \
[ ] implement evaluation logic

More long term goals:
* Create chess games database, by either designing one from scratch or creating an
  interface for an SQL or NoSQL database.
  * games should be stored compactly
  * do fast queries for games
* Create beginning game chess database.
* Create end game chess database.
* Use machine learning techniques to train evaluation functions.
* Explore GUI options
  * What are good open source chess engine GUIs?
  * What would it take to create one from scratch?
* Investigate chess engine standards?
  * What are other chess engines doing that *zoor* should do.
