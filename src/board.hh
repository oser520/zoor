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


class Board {
  friend std:ostream& operator<<(std:ostream &os, const Board &board);
  
public:
  using dim_type = unsigned short;
  using row_type = uint64_t;
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
  ~Board() noexcept = default;

  /* return the piece count */
  PieceCount pieceCount() noexcept;

  /* Return a vector of all the legal moves from this position.
   * 
   * If there are no legal moves, then the vector of boards will be empty. This
   * mean that the current position is a checkmate, a stalemate, or that there
   * are no pieces on the board. 
   *
   * @return A vector of all the legal moves from the current position.
   */
  vector<Board> moves() noexcept;

  PieceCount whiteCount() noexcept;
  PieceCount blackCount() noexcept;
};

} // namespace zoor

#endif 
