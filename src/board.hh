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
#include "piececode.hh"

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
  friend bool operator==(const Board &boar1, const Board &board2) noexcept;
  
public:
  using dim_type = unsigned short;
  using row_type = uint64_t;
  static constexpr dim_type BOARD_DIM = 8;
  
private:
  array<row_type, BOARD_DIM> mRows;
  PieceCode mColorMove;
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

  /* Return a vector of all the legal moves from this position.
   * 
   * If there are no legal moves, then the vector of boards will be empty. This mean
   * that the current position is a checkmate, a stalemate, or that there are no
   * pieces on the board. 
   *
   * @return A vector of all the legal moves from the current position.
   */
  vector<Board> moves() const noexcept;

  /**
   * @brief Obtain the count of white pieces on the board. The object is not modified
   * and no exceptions are thrown.
   *
   * @return A copy of the white PieceCount.
   */
  PieceCount whiteCount() const noexcept;

  /**
   * @brief Obtain the count of black pieces on the board. The object is not modified
   * and no exceptions are thrown.
   *
   * @return A copy of the black PieceCount.
   */
  PieceCount blackCount() const noexcept;
};

/**
 * Writes the current board position to an output stream.
 *
 * @param os The output stream.
 * @param board The board.
 * @return The output stream.
 */
std:ostream& operator<<(std:ostream &os, const Board &board);

/**
 * Equality operator for a *Board*.
 *
 * The board position, and who's turn is it to play determine the uniqueness of a
 * board, and whether two boards are equal or not. Therefore, it is enough to look
 * the eight rows and who's turn it is.
 *
 * @param board1 The first board.
 * @param board2 The second board.
 * @return True if boards are equal, false otherwise.
 * @except Guaranteed not to throw an exception.
 */
bool operator==(const Board &boar1, const Board &board2) noexcept;

/**
 * Non-equality operator for a *Board*.
 *
 * The board position, and who's turn is it to play determine the uniqueness of a
 * board, and whether two boards are equal or not. Therefore, it is enough to look
 * the eight rows and who's turn it is.
 *
 * @param board1 The first board.
 * @param board2 The second board.
 * @return False if boards are equal, true otherwise.
 * @except Guaranteed not to throw an exception.
 */
bool operator!=(const Board &boar1, const Board &board2) noexcept;

} // namespace zoor

#endif 
