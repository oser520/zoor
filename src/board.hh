/**
 * @file board.hh
 * @author Omar A Serrano
 * @date 2015-12-18
 */

#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>

namespace zoor {

/* TODO:
 * - create piece representation based on 4 bits
 * - determine how to represent board (e.g. use dynamic memory?) 
 * - provide member variables to maintain information, including
 *   - 50 move tie
 *   - 3 move tie
 *   - number of moves in game so far
 *   - black/whites turn
 *   - number of pieces
 * - provide member functions
 *   - get next move
 *   - serialize board
 *   - get position value
 *   - info about position
 *   - is mate
 */

/**
 * PieceCount maintains a count of the number of pieces on the board.
 */
struct PieceCount {
  using count_type = unsigned short;

  count_type mKings;
  count_type mQueens;
  count_type mRooks;
  count_type mBishops;
  count_type mKnights;
  count_type mPawns;
  count_type mTotal;

  /* copy control */
  PieceCount() noexcept = default;
  PieceCount(const PieceCount &pcount) noexcept = default;
  PieceCount& operator=(const PieceCount &pcount) noexcept = default;
  ~PieceCount() noexcept = default;

  /**
   * clear() Clears the board of pieces.
   * @return a reference to this PieceCount
   */
  PieceCount& clear() noexcept;

  /**
   * init() Sets the number of pieces to what they are when the game begins.
   * @return a reference to this PieceCount
   */
  PieceCount& init() noexcept;
};

class Board {
  friend std:ostream& operator<<(std:ostream &os, const Board &board);
  unsigned int mRows[8];
public:
  /* copy control */
  Board() = default;
  Board(const Board &board) = default;
  Board(Board &&board) = default;
  Board& operator=(const Board &board) = default;
  Board& operator=(Board &&board) = default;
  ~Board() = default;
};

} // namespace zoor

#endif 
