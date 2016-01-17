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
#include <utility>

// zoor headers
#include "piececount.hh"
#include "square.hh"
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
  /**
   * The actual board, in the sense that 8 bits represent one square, and each row
   * cotains 8 squares.
   */
  array<row_type, BOARD_DIM> mRows;

  /**
   * Indicates the player's turn: either white or black moves.
   */
  PieceColor mColorMove;

  /**
   * The count of white pieces on the board.
   */
  PieceCount mWhiteCount;

  /**
   * The count of black pieces on the board.
   */
  PieceCount mBlackCount;

  /**
   * The last move. The first @c Square is the piece that made the move, and the
   * second @c Square is where the piece moves.
   */
  pair<Square, Square> mLastMove;

  /* @brief Return a vector of all the legal moves from the given position.
   * @param row The row in the board.
   * @param col The column in the board.
   * @return A vector of all the legal moves from the current position. An empty
   *  vector if there are no moves from the given position.
   */
  vector<PieceMoves> getMoves(dim_type row, dim_type col) const noexcept;

  /**
   * @brief Make a move and return a new board.
   * @detail Does not affect last move on the current board, nor any other aspect of
   *  the board.
   * @param square1 The @c Square that is making the move. The Square must contain a
   *  valid piece with a valid color.
   * @param square2 The @c Square where the piece is moving to. If it contains a
   *  piece, then it represents a capture.
   * @return A copy of the board after the move.
   * @throw Never throws.
   */
  Board moveCopy(const Square &square1, const Square &square2) const noexcept;

  /**
   * @brief Make a move on the board.
   * @detail The move becomes the last move made.
   * @param square1 The @c Square that is making the move. The Square must contain a
   *  valid piece with a valid color.
   * @param square2 The @c Square where the piece is moving to. If it contains a
   *  piece, then it represents a capture.
   * @return A reference to this @c Board.
   * @throw Never throws.
   */
  Board& moveRef(const Square &square1, const Square &square2) noexcept;

public:
  /**
   * @brief Default constructor.
   * @detail Initializes a board with the standard number of pieces, with
   *  white's turn to move.
   */
  Board();

  /**
   * @brief Default copy constructor.
   * @param board The @c Board being copied.
   */
  Board(const Board &board) = default;

  /**
   * @brief Default move constructor.
   * @param board The @c Board being moved.
   */
  Board(Board &&board) = default;

  /**
   * @brief Default copy assignment.
   * @param board The @c Board being copied.
   */
  Board& operator=(const Board &board) = default;

  /**
   * @brief Default move assignment.
   * @param board The @c Board being moved.
   */
  Board& operator=(Board &&board) = default;

  /**
   * @brief Default move destructor.
   * @throw Never throws.
   */
  ~Board() noexcept = default;

  /* @brief Return a vector of all the boards that can be reached from this board in
   *  one move.
   * @detail If there are no legal moves, then the vector of boards will be empty.
   *  This may mean that the current position is a checkmate, a stalemate, or that
   *  there are no pieces on the board.
   * @return A vector of all the legal moves from the current position.
   */
  vector<Board> getBoardsFromMoves() const noexcept;

  /**
   * @brief Make a move and return a new board.
   * @detail This does not affect the last move of the current board, only the last
   *  move of the board on which the move is made (i.e., the copy of the board).
   * @param square1 The @c Square that is making the move. The Square must contain a
   *  valid piece with a valid color.
   * @param square2 The @c Square where the piece is moving to. If it contains a
   *  piece, then it represents a capture.
   * @return A copy of the new @c Board after the move.
   * @throw Never throws.
   */
  Board makeMoveCopy(const Square &square1, const Square &square2) const noexcept;

  /**
   * @brief Make a move the current board.
   * @detail This move will become the new last move.
   * @param square1 The @c Square that is making the move. The Square must contain a
   *  valid piece with a valid color.
   * @param square2 The @c Square where the piece is moving to. If it contains a
   *  piece, then it represents a capture.
   * @return A reference to this @c Board.
   * @throw Never throws.
   */
  Board& makeMove(const Square &square1, const Square &square2) noexcept;

  /**
   * @brief Reverses the last move.
   * @return A reference to this board.
   * @throw Never throws exception.
   */
  Board& undo() noexcept;

  /**
   * @brief Obtain the count of white pieces on the board. The object is not modified
   *  and no exceptions are thrown.
   * @return A copy of the white PieceCount.
   */
  PieceCount whiteCount() const noexcept;

  /**
   * @brief Obtain the count of black pieces on the board. The object is not modified
   *  and no exceptions are thrown.
   * @return A copy of the black PieceCount.
   */
  PieceCount blackCount() const noexcept;

  /**
   * @brief Get the last move made on this board.
   * @return A copy of the last move.
   * @throw Never throws.
   */
  pair<Square, Square> lastMove() const noexcept;
};

/**
 * @brief Writes the current board position to an output stream.
 * @param os The output stream.
 * @param board The board.
 * @return The output stream.
 */
std:ostream& operator<<(std:ostream &os, const Board &board);

/**
 * @brief Equality operator.
 * @detail The board position, and who's turn is it to play determine the uniqueness
 *  of a board, and whether two boards are equal or not. Therefore, it is enough to
 *  look the eight rows and who's turn it is.
 * @param board1 The first board.
 * @param board2 The second board.
 * @return True if boards are equal, false otherwise.
 * @except Guaranteed not to throw an exception.
 */
bool operator==(const Board &boar1, const Board &board2) noexcept;

/**
 * @brief Non-equality operator.
 * @detail The board position, and who's turn is it to play determine the uniqueness
 *  of a board, and whether two boards are equal or not. Therefore, it is enough to
 *  look the eight rows and who's turn it is.
 * @param board1 The first board.
 * @param board2 The second board.
 * @return False if boards are equal, true otherwise.
 * @except Guaranteed not to throw an exception.
 */
bool operator!=(const Board &boar1, const Board &board2) noexcept;

} // namespace zoor

#endif 
