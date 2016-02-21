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
#include <iterator>
#include <stdexcept>

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemove.hh"

namespace zoor {

// forward declaration
class BoardIterator;

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
  friend BoardIterator;
  friend std:ostream& operator<<(std:ostream &os, const Board &board);
  friend bool operator==(const Board &boar1, const Board &board2) noexcept;
  
public:
  /**
   * Alias for the type of the dimension of the @c Board.
   */
  using dim_type = short;

  /**
   * Alias for the type of the row of the @c Board.
   */
  using row_type = uint64_t;

  /**
   * Alias for the iterator.
   */
  using iterator = BoardIterator;

  /**
   * Alias for a vector of jump positions.
   */
  using jump_list = std::vector<std::pair<dim_type, dim_type>>;

  /**
   * Specifies the number of rows and columns on the @c Board.
   */
  static constexpr dim_type BOARD_DIM = 8;

  /**
   * The jump deltas for a knight.
   */
  static const jump_list JUMP_KNIGHT;

  /**
   * The jump deltas for a king.
   */
  static const jump_list JUMP_KING;
  
private:
  /**
   * The actual board, in the sense that 8 bits represent one square, and each row
   * cotains 8 squares.
   */
  array<row_type, BOARD_DIM> mRows;

  /**
   * Indicates the player's turn: either white or black moves.
   */
  PieceColor mColor;

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
  PieceMove mLastMove;

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

  /**
   * @brief Get a list of jump positions that are legal from a given row and column.
   * @param row The row where the jump is being made from.
   * @param column The column where the jump is being made from.
   * @return positions The list of jumping positions.
   * @throw Never throws.
   */
  jump_list
  jump(dim_type row, dim_type column, const jump_list &positions) const noexcept;

  /**
   * @brief Determine if there is a  check at the given row and column from a piece
   *  in the diagonal up and to the right.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckNE(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a  check at the given row and column from a piece
   *  in the diagonal down and to the right.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckSE(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a  check at the given row and column from a piece
   *  in the diagonal down and to the left.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckSW(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a  check at the given row and column from a piece
   *  in the diagonal up and to the left.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckNW(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a pawn check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckPawn(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a knight check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckKnight(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a bishop check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckBishop(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a rook check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckRook(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a queen check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckQueen(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a king check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheckKing(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   * @throw Never throws.
   */
  bool isCheck(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Determine if there is an en passant at a given column.
   * @param color The @c PieceColor.
   * @param toColumn The column where there might be an en passant.
   * @return True if there is an en passant at the given column.
   * @throw Never throws.
   */
  bool isEnPassant(PieceColor color, dim_type toColumn) const noexcept;

  /**
   * @brief Move the pawn at the given row and column.
   * @param row The row where the pawn is located.
   * @param column The column where the pawn is located.
   * @return A vector of moves.
   * @throw Never throws.
   */
  std::vector<PieceMove> movePawn(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Move the knight at the given row and column.
   * @param row The row where the knight is located.
   * @param column The column where the knight is located.
   * @return A vector of squares where the knight can move.
   * @throw Never throws.
   */
  std::vector<PieceMove> moveKnight(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Move the bishop at the given row and column.
   * @param row The row where the bishop is located.
   * @param column The column where the bishop is located.
   * @return A vector of squares where the bishop can move.
   * @throw Never throws.
   */
  std::vector<PieceMove> moveBishop(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Move the rook at the given row and column.
   * @param row The row where the rook is located.
   * @param column The column where the rook is located.
   * @return A vector of squares where the rook can move.
   * @throw Never throws.
   */
  std::vector<PieceMove> moveRook(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Move the queen at the given row and column.
   * @param row The row where the queen is located.
   * @param column The column where the queen is located.
   * @return A vector of squares where the queen can move.
   * @throw Never throws.
   */
  std::vector<PieceMove> moveQueen(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Move the king at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return A vector of squares where the king can move.
   * @throw Never throws.
   */
  std::vector<PieceMove> moveKing(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Get the bit pattern at a specific row and column in the @c Board.
   * @param row The row to get the pattern from.
   * @param column The column to get the bit pattern from.
   * @return An unsigned char representing the bit pattern.
   * @throw Never throws.
   */
  unsigned char get(dim_type row, dim_type column) const noexcept
  {
    return static_cast<unsigned char>((mRows[row] >> (column * BOARD_DIM)) & 0xff);
  }

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

  /**
   * @brief Determine if position is within bounds of board.
   * @param position The position in question.
   * @return True if position is within bounds of board.
   * @throw Never throws.
   */
  static bool isInBound(dim_type position) const noexcept;

  /**
   * @brief Determine if row and column are in bounds.
   * @param row The row of the position.
   * @param column The column of the position.
   * @return True if position is within bounds of board.
   * @throw Never throws.
   */
  static bool isInBound(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Return a reference to the rows of the board.
   * @return A constant reference to the rows of the board.
   * @throw Never throws.
   */
  const std:array<row_type, BOARD_DIM>& rows() const noexcept;

  /**
   * @brief Return a copy of the rows of the board.
   * @return A copy of the rows of the board.
   */
  std:array<row_type, BOARD_DIM> rowsCopy() const;

  /* @brief Return a vector of all the legal moves from the given position.
   * @param row The row in the board.
   * @param col The column in the board.
   * @return A vector of all the legal moves from the current position. An empty
   *  vector if there are no moves from the given position.
   */
  std::vector<PieceMove> getMoves(dim_type row, dim_type col) const noexcept;

  /* @brief Return a vector of all the boards that can be reached from this board in
   *  one move.
   * @detail If there are no legal moves, then the vector of boards will be empty.
   *  This may mean that the current position is a checkmate, a stalemate, or that
   *  there are no pieces on the board.
   * @return A vector of all the legal moves from the current position.
   */
  std::vector<Board> getBoardsFromMoves() const noexcept;

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
  PieceMove lastMove() const noexcept;

  /**
   * @brief Get the contents of a @c Square at a given row and column.
   * @param row The row of the @c Board.
   * @param column The column of the @c Board.
   * @return A copy of the @c Square at the specified row and column.
   * @throw Never throws.
   */
  Square operator()(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Provide an iterator to the first @c Square in the @c Board.
   * @detail The iterator cannot modify the @c Board.
   * @return An iterator to the first @c Square.
   * @throw Never throws.
   */
  iterator begin() const noexcept;

  /**
   * @brief Provide an iterator to one past the last @c Square in the @c Board.
   * @return An iterator to one past the last @c Square in the board.
   * @throw Never throws.
   */
  iterator end() const noexcept;
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

// BoardIterator

/**
 * BoardIterator exception.
 */
class BoardIteratorError: public std:logic_error
{
public:
  explicit BoardIteratorError(const std::string& what_arg) noexcept
    : logic_error(what_arg) {}

  explicit BoardIteratorError(const char *what_arg) noexcept
    : logic_error(what_arg) {}

  virtual ~BoardIteratorError() noexcept = default;
};

/**
 * @brief Provides an iterator interface to access each @c Square of a @c Board.
 * @detail The iterators can only read the board, and connot modify it.
 */
class BoardIterator
  : std:iterator<std:random_access_iterator_tag, Square, dim_type>
{
  // see the comments for these declarations below
  friend bool operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;
  friend difference_type
  operator-(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;
  friend BoardIterator operator-(const BoardIterator &bi, difference_type value);
  friend BoardIterator operator+(const BoardIterator &bi, difference_type value);

// TODO: implement BoardIteratorError
public:
  /**
   * Alias for the type of the dimension of a @c Board.
   */
  using dim_type = Board::dim_type;

  /**
   * @brief The number of squres in a row.
   * @detail Also represents the number of squares in a column.
   */
  static constexpr dim_type LAST_INDEX = Board::BOARD_DIM * Board::BOARD_DIM;

  /**
   * Default constructor is deleted.
   */
  BoardIterator() = delete;

  /**
   * @brief Constructs iterator to first @c Square on a @c Board.
   * @param board Pointer to the @c Board.
   * @throw Never throws.
   */
  BoardIterator(const Board *board) noexcept;

  /**
   * @brief Constructs iterator to one past the last @c Square on a @c Board.
   * @detail Second paramter is ignored, but differentiates this function from the
   *  constructor with one paramter to construct the <em>end</em> iterator.
   * @param board Pointer to the @c Board.
   * @throw Never throws.
   */
  BoardIterator(Board const *board, int) noexcept;

  /**
   * @brief Default copy constructor.
   * @param boardIterator The @c BoardIterator being copied.
   * @throw Never throws.
   */
  BoardIterator(const BoardIterator &boardIterator) noexcept = default;

  /**
   * @brief Default move constructor.
   * @param boardIterator The @c BoardIterator being moved.
   * @throw Never throws.
   */
  BoardIterator(BoardIterator &&boardIterator) noexcept = default;

  /**
   * @brief Default copy assignment.
   * @param boardIterator The @c BoardIterator being copied.
   * @throw Never throws.
   */
  BoardIterator& operator=(const BoardIterator &boardIterator) noexcept = default;

  /**
   * @brief Default move assignment.
   * @param boardIterator The @c BoardIterator being moved.
   * @throw Never throws.
   */
  BoardIterator& operator=(BoardIterator &&boardIterator) noexcept = default;

  /**
   * @brief Default destructor.
   * @throw Never throws.
   */
  ~BoardIterator() noexcept = default;

  /**
   * @brief Get the next @c BoardIterator.
   * @return A reference to the next @c BoardIterator.
   * @throw BoardIteratorError if next iterator yields one past the last iterator.
   */
  BoardIterator& operator++();

  /**
   * @brief Get a copy of the current iterator, but move it forward.
   * @return A copy of the iterator before moving it forward.
   * @throw BoardIteratorError if next iterator yields one past the last iterator.
   */
  BoardIterator operator++(int);

  /**
   * @brief Move the iterator forward by a given value.
   * @param value The value by which the iterator should move forward.
   * @return A reference to the iterator after being moved.
   * @throw BoardIteratorError if iterator is moved beyond end iterator.
   */
  BoardIterator& operator+=(difference_type value);

  /**
   * @brief Move the iterator backward by a given value.
   * @param value The value by which the iterator should move backward.
   * @return A reference to the iterator after being moved.
   * @throw BoardIteratorError if value takes the iterator beyond zero.
   */
  BoardIterator& operator-=(difference_type value);

  /**
   * @brief Obtain a @c Square from the iterator.
   * @detail The @c Baord cannot be modified via the @c Square.
   * @return A @c Square that represents the current position of the iterator in the
   *  @c Board.
   * @throw BoardIteratorError if this is the end iterator.
   */
  value_type operator*() const;

private:
  /**
   * A pointer to the @c Board.
   */
  const Board *mBoardPtr;

  /**
   * @brief The current index in the @Board.
   * @detail Index goes from 0 to 63.
   */
  difference_type mIndex;
};

/**
 * @brief Equality operator.
 * @param bi1 A reference to the first @c BoardIterator.
 * @param bi2 A reference to the second @c BoardIterator.
 * @return The iterators are only equal if they point to the same @c Square on the
 *  same @c Board.
 * @throw Never throws.
 * TODO: make definition inline after it has been tested
 */
bool operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;

/**
 * @brief Non-equality operator.
 * @param bi1 A reference to the first @c BoardIterator.
 * @param bi2 A reference to the second @c BoardIterator.
 * @return The iterators are only equal if they point to the same @c Square on the
 *  same @c Board.
 * @throw Never throws.
 * TODO: make definition inline after it has been tested
 */
bool operator!=(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;

/**
 * @brief Subtraction operator.
 * @param bi1 A reference to the first @c BoardIterator.
 * @param bi2 A reference to the second @c BoardIterator.
 * @return The difference between the iterators, of type difference_type.
 * @throw Never throws.
 * TODO: make definition inline after it has been tested
 */
BoardIterator::difference_type
operator-(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;

/**
 * @brief Subtraction operator between @c BoardIterator and @c difference_type.
 * @param bi A reference to the @c BoardIterator.
 * @param value The value by which the iterator should advance or move backward.
 * @return A new iterator pointing to the location where <em>value</em> took
 *  <em>bi</em>.
 * @throw BoardIteratorError if <em>value</em> moves <em>bi</em> beyond the board,
 *  excluding the end iterator.
 * TODO: make definition inline after it has been tested
 */
BoardIterator
operator-(const BoardIterator &bi, BoardIterator::difference_type value);

/**
 * @brief Addition operator between @c BoardIterator and @c difference_type.
 * @param bi A reference to a @c BoardIterator.
 * @param value The value by which the iterator should advance or move backward.
 * @return A new iterator pointing to the location where <em>value</em> took
 *  <em>bi</em>.
 * @throw BoardIteratorError if <em>value</em> moves <em>bi</em> beyond the board,
 *  excluding the end iterator.
 * TODO: make definition inline after it has been tested
 */
BoardIterator
operator+(const BoardIterator &bi, BoardIterator::difference_type value);

} // namespace zoor

#endif 
