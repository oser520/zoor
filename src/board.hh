/**
 * @file board.hh
 * @author Omar A Serrano
 * @date 2015-12-18
 */

#ifndef _BOARD_H
#define _BOARD_H

// standard headers
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

// zoor headers
#include "piececount.hh"

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

class Board {
  friend std:ostream& operator<<(std:ostream &os, const Board &board);
  
public:
  using dim_type = unsigned short;
  using row_type = uint32_t;

  static constexpr dim_type BOARD_DIM = 8;
  

private:
  array<row_type, BOARD_DIM> mRows;
  PieceCount mWhiteCount;
  PieceCount mBlackCount;

public:
  /* copy control */
  Board() = default;
  Board(const Board &board) = default;
  Board(Board &&board) = default;
  Board& operator=(const Board &board) = default;
  Board& operator=(Board &&board) = default;
  ~Board() = default;

  /* return the piece count */
  PieceCount pieceCount() noexcept;

  /* return a vector of all the legal moves from this position */
  vector<Board> moves() noexcept;

  PieceCount whiteCount() noexcept;
  PieceCount blackCount() noexcept;
};

} // namespace zoor

#endif 
