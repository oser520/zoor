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


/**
 * The Board class maintains the current state of the chess board.
 *
 * The functionality of the Board class is limited to the minimum knowledge we would
 * expect a board to have about itself, including the current chess position, the
 * number of pieces on the board, the positions that can be obtained from the current
 * position via legal moves, and whether it is white's or black's turn to move. On
 * the other hand, we don't expect a chess board to know the series of moves that led
 * to the current position. It is in fact feasible that we arrived at the current
 * position without any prior moves if we are not playing a game but only analysing a
 * position. In real life, it is the player's job to know the series of moves that
 * led to a given position.
 */
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
   * If there are no legal moves, then the vector of boards will be empty. This mean
   * that the current position is a checkmate, a stalemate, or that there are no
   * pieces on the board. 
   *
   * @return A vector of all the legal moves from the current position.
   */
  vector<Board> moves() noexcept;

  PieceCount whiteCount() noexcept;
  PieceCount blackCount() noexcept;
};

} // namespace zoor

#endif 
