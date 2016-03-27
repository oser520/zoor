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
#include <bitset>
#include <string>
#include <functional>

// zoor headers
#include "piececode.hh"
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
  friend std::ostream& operator<<(std::ostream &os, const Board &board);
  friend bool operator==(const Board &board1, const Board &board2) noexcept;
  
public:
  /**
   * Alias for the type of the dimension of the @c Board.
   */
  using dim_type = short;

  /**
   * Alias for the type of the row of the @c Board.
   */
  using row_type = std::array<piececode_t, 8>;

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

  /**
   * Used to initialize the board at construction.
   */
  static const std::array<row_type, BOARD_DIM> INIT_BOARD;

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
   * @brief Uses a list of squres to construct board.
   * @param squareList The list of pieces to put on the board.
   * @param color The color to move next.
   * @param boardInfo A bitset with information about board.
   * @param lastMove The last move made.
   * @throw Never throws.
   */
  Board
    (const std::vector<Square> &squareList,
     const PieceColor color,
     const BoardInfo<16> &boardInfo,
     const PieceMove &lastMove = PieceMove()) noexcept;

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
   * @brief Determine if the king whose turn is it to move can do short castling.
   * @return True if the king can do short castling.
   * @throw Never throws.
   */
  bool canCastle() const noexcept;

  /**
   * @brief Determine if the king whose turn is it to move can do long castling.
   * @return True if the king can do long castling.
   * @throw Never throws.
   */
  bool canCastleLong() const noexcept;

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
  std::vector<PieceMove> getMoves(dim_type row, dim_type col) const;

  /* @brief Return a vector of all the legal moves from all the pieces on the board.
   * @param row The row in the board.
   * @param col The column in the board.
   * @return A vector of all the legal moves from the all the pieces on the board.
   *  An empty vector if there are no moves from the given position.
   */
  std::vector<PieceMove> getMoves() const;

  /* @brief Return a vector of all the boards that can be reached from this board in
   *  one move.
   * @detail If there are no legal moves, then the vector of boards will be empty.
   *  This may mean that the current position is a checkmate, a stalemate, or that
   *  there are no pieces on the board.
   * @return A vector of all the legal moves from the current position.
   */
  std::vector<Board> getBoards() const;

  /**
   * @brief Make a move and return a new board.
   * @detail Meant to be used to take a board to a position.
   * @detail Does not affect the state of this board.
   * @param pieceMove The @c PieceMove.
   * @return A copy of the new @c Board after the move.
   * @TODO throw exception if the move is not legal (ChessError)
   */
  Board makeMoveCopy(const PieceMove &pieceMove) const;

  /**
   * @brief Make a move on the current board.
   * @detail This move will become the new last move. Meant to be used to take a
   *  board to a position.
   * @param pieceMove The @c PieceMove.
   * @return A reference to this @c Board.
   * @throw Never throws.
   * @TODO throw exception if the move is not legal (ChessError)
   */
  Board& makeMove(const PieceMove &pieceMove);

  /**
   * @brief Get the last move made on this board.
   * @return A copy of the last move.
   * @throw Never throws.
   */
  PieceMove lastMove() const noexcept;

  /**
   * @brief Check if the last move is valid, given the current position.
   * @return True if the last move is valid, false otherwise.
   * @throw Never throws.
   */
  bool isLastMoveOk() const noexcept;

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

  /**
   * @brief Get a list of jump positions that are legal from a given row and column.
   * @param row The row where the jump is being made from.
   * @param column The column where the jump is being made from.
   * @return positions The list of jumping positions.
   * @throw Never throws.
   */
  jump_list
  jump(dim_type row, dim_type column, const jump_list &positions) const;

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
   */
  bool isCheckKnight(dim_type row, dim_type column) const;

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
   */
  bool isCheckKing(dim_type row, dim_type column) const;

  /**
   * @brief Determine if there is a check at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return True if there is a check at the given square.
   */
  bool isCheck(dim_type row, dim_type column) const;

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
   */
  std::vector<PieceMove> movePawn(dim_type row, dim_type column) const;

  /**
   * @brief Move the knight at the given row and column.
   * @param row The row where the knight is located.
   * @param column The column where the knight is located.
   * @return A vector of squares where the knight can move.
   */
  std::vector<PieceMove> moveKnight(dim_type row, dim_type column) const;

  /**
   * @brief Move the bishop at the given row and column.
   * @param row The row where the bishop is located.
   * @param column The column where the bishop is located.
   * @return A vector of squares where the bishop can move.
   */
  std::vector<PieceMove> moveBishop(dim_type row, dim_type column) const;

  /**
   * @brief Move the rook at the given row and column.
   * @param row The row where the rook is located.
   * @param column The column where the rook is located.
   * @return A vector of squares where the rook can move.
   */
  std::vector<PieceMove> moveRook(dim_type row, dim_type column) const;

  /**
   * @brief Move the queen at the given row and column.
   * @param row The row where the queen is located.
   * @param column The column where the queen is located.
   * @return A vector of squares where the queen can move.
   */
  std::vector<PieceMove> moveQueen(dim_type row, dim_type column) const;

  /**
   * @brief Move the king at the given row and column.
   * @param row The row where the king is located.
   * @param column The column where the king is located.
   * @return A vector of squares where the king can move.
   */
  std::vector<PieceMove> moveKing(dim_type row, dim_type column) const;

  /**
   * @brief Return string representation of the board.
   * @return A string representing the board.
   */
  std::string toString() const;

  /**
   * @brief Get the hash code for this board.
   * @details Hashes the raw contents of the board and the color reprsenting whose
   *  turn is it to move, which are also the two characteristics used to determine
   *  equality. Implemented using One-at-a-Time hash
   * @return The numeric hash code for this board.
   */
  size_t hashCode() const noexcept;

  /**
   * @brief Get the color of whose turn it is to move.
   * @return The color of the player whose turn it is to move.
   */
  PieceColor colorToMove() const noexcept;

private:
  /**
   * @brief Make a move on a new board.
   * @detail Does not affect state of this board.
   * @param pieceMove The @c PieceMove.
   * @return A copy of the board after the move.
   */
  Board moveCopy(const PieceMove &pieceMove) const;

  /**
   * @brief Make a move on the board.
   * @detail The move becomes the last move made.
   * @param pieceMove The @c PieceMove.
   * @return A reference to this @c Board.
   * @throw Never throws.
   */
  Board& moveRef(const PieceMove &pieceMove) noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the diagonal up and to the right.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckNE(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the diagonal down and to the right.
   * @detail Can use this to determine if there is a check from a bishop or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckSE(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
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
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the column from above.
   * @detail Can use this to determine if there is a check from a rook or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckN(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the row from the right.
   * @detail Can use this to determine if there is a check from a rook or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckE(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the column from below.
   * @detail Can use this to determine if there is a check from a rook or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckS(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Determine if there is a check at the given row and column from a piece
   *  in the row from the left.
   * @detail Can use this to determine if there is a check from a rook or a queen.
   * @param row The row where the king might be located.
   * @param column The column where the king might be located.
   * @return True if there is a check.
   * @throw Never throws.
   */
  bool isCheckW(dim_type row, dim_type column, PieceCode piece) const noexcept;

  /**
   * @brief Get the bit pattern at a specific row and column in the @c Board.
   * @param row The row to get the pattern from.
   * @param column The column to get the bit pattern from.
   * @return An unsigned char representing the bit pattern.
   * @throw Never throws.
   */
  piececode_t get(dim_type row, dim_type column) const noexcept;

  /**
   * @brief Put a bit pattern for a piece on the board.
   * @param row The row of the location.
   * @param column The column of the location.
   * @param code The bit pattern representing the piece.
   * @throw Never throws.
   */
  void put(dim_type row, dim_type column, piececode_t code) noexcept;

  /**
   * @brief Put a bit pattern for a piece on the board.
   * @detail Uses the current color for the color of the piece.
   * @param row The row of the location.
   * @param column The column of the location.
   * @param piece The @c PieceCode.
   * @throw Never throws.
   */
  void put(dim_type row, dim_type column, PieceCode piece) noexcept;

  /**
   * @brief Put a bit pattern for a piece on the board.
   * @param row The row of the location.
   * @param column The column of the location.
   * @param piece The @c PieceCode.
   * @param color The @c PieceColor.
   * @throw Never throws.
   */
  void
  put(dim_type row, dim_type column, PieceCode piece, PieceColor color) noexcept;

  /**
   * @brief Clear the bits in a square.
   * @param row The row of the location.
   * @param column The column of the location.
   * @return The bit pattern in the square.
   * @throw Never throws.
   */
  piececode_t clearSq(dim_type row, dim_type column) noexcept;

  /**
   * The actual board, in the sense that 8 bits represent one square, and each row
   * cotains 8 squares.
   */
  std::array<row_type, BOARD_DIM> mRows;

  /**
   * Indicates the player's turn: either white or black moves.
   */
  PieceColor mColor;

  /**
   * The last move. The first @c Square is the piece that made the move, and the
   * second @c Square is where the piece moves.
   */
  PieceMove mLastMove;

  /**
   * @brief Maintains information that impacts the moves a player can make.
   * @detail Maintains the following information:
   * @li 1. The rook at <em>a1</em> has moved.
   * @li 2. The rook at <em>h1</em> has moved.
   * @li 3. The white king has moved.
   * @li 4. The white king is in check.
   * @li 5. Mate for white king.
   * @li 6. The rook at <em>a8</em> has moved.
   * @li 7. The rook at <em>h8</em> has moved.
   * @li 8. The black king has moved.
   * @li 9. The black king is in check.
   * @li 10. Mate for black king.
   * This information is mainly used to check if the king can do castling,
   * if the king must move because it is in check, or it is check mate.
   */
  std::bitset<16> mBoardInfo;

  /**
   * Bit indexes for <em>mBoardInfo</em>.
   */
  enum {
    RK_A1_MOVED, RK_H1_MOVED, WK_MOVED, WK_CHECK, WK_MATE,
    RK_A8_MOVED, RK_H8_MOVED, BK_MOVED, BK_CHECK, BK_MATE
  };

}; // Board

/**
 * @brief Writes the current board position to an output stream.
 * @param os The output stream.
 * @param board The board.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream &os, const Board &board);

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
 * @brief Provides an iterator interface to access each @c Square of a @c Board.
 * @detail The iterators can only read the board, and connot modify it.
 */
class BoardIterator
  : std:iterator<std:random_access_iterator_tag, piececode_t, Board::dim_type>
{
  // see the comments for these declarations below
  friend bool operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;
  friend difference_type
  operator-(const BoardIterator &bi1, const BoardIterator &bi2) noexcept;
  friend BoardIterator operator-(const BoardIterator &bi, difference_type value);
  friend BoardIterator operator+(const BoardIterator &bi, difference_type value);

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
   * @param board Reference to the @c Board.
   * @throw Never throws.
   */
  BoardIterator(const Board &board) noexcept;

  /**
   * @brief Constructs iterator to one past the last @c Square on a @c Board.
   * @detail Second paramter is ignored, but differentiates this function from the
   *  constructor with one paramter to construct the <em>end</em> iterator.
   * @param board Reference to the @c Board.
   * @throw Never throws.
   */
  BoardIterator(Board const &board, int) noexcept;

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
   * @brief Obtain the piece code from the iterator.
   * @detail Only provides read access.
   * @return The piece code in the square.
   * @throw ChessError if iterator is <em>end</em> iterator.
   */
  value_type operator*() const;

  /**
   * @brief Obtain the piece from the iterator.
   * @detail Only provides read access.
   * @return The piece in the square.
   * @throw ChessError if iterator is <em>end</em> iterator.
   */
  PieceCode piece() const;

  /**
   * @brief Obtain the piece's color from the iterator.
   * @detail Only provides read access.
   * @return The color of the piece in the square.
   * @throw ChessError if iterator is <em>end</em> iterator.
   */
  PieceColor color() const;

  /**
   * @brief Obtain the current row.
   * @return The row of the current square.
   * @throw ChessError if iterator is <em>end</em> iterator.
   */
  dim_type row() const;

  /**
   * @brief Obtain the current column.
   * @return The column of the current square.
   * @throw ChessError if iterator is <em>end</em> iterator.
   */
  dim_type column() const;

private:
  /**
   * A pointer to the @c Board.
   */
  const Board mBoard;

  /**
   * @brief The current index in the @Board.
   * @detail Index goes from 0 to 63.
   */
  difference_type mIndex;

  /**
   * The code representing the piece on the current square.
   */
  piececode_t mCode;
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

namespace std {

/**
 * Board specialization for <em>hash</em>. Needs to be defined within std namespece.
 */
template<>
struct hash<zoor::Board>
{
  using argument_type = zoor::Board;
  using result_type = size_t;

  result_type operator()(const argument_type& arg)
  {
    return arg.hashCode();
  }
};

} // std

#endif 
