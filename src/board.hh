/////////////////////////////////////////////////////////////////////////////////////
/// @file board.hh
/// @author Omar A Serrano
/// @date 2015-12-18
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOARD_H
#define _BOARD_H

//
// standard headers
//
#include <cassert>
#include <cstdint>
#include <functional>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

//
// zoor headers
//
#include "basictypes.hh"
#include "basicboard.hh"
#include "boardinfo.hh"
#include "chesserror.hh"
#include "piecemove.hh"
#include "square.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief The Board class maintains the current state of the chess board.
/// @details The functionality of the Board class is limited to the minimum knowledge we would
/// expect a board to have about itself, including the current chess position, the
/// number of pieces on the board, the positions that can be obtained from the current
/// position via legal moves, and whether it is white's or black's turn to move. On
/// the other hand, we don't expect a chess board to know the series of moves that led
/// to the current position. It is in fact feasible that we arrived at the current
/// position without any prior moves if we are not playing a game but only analysing a
/// position. In real life, it is the player's job to know the series of moves that
/// led to a given position.
///
class Board {
public:
  ///
  /// @brief The board iterator
  ///
  using iterator = BasicBoard::iterator;

  ///
  /// @brief The const board iterator
  ///
  using const_iterator = BasicBoard::const_iterator;

  ///
  /// @brief Alias for a vector of jump positions.
  ///
  using jump_list = std::vector<std::pair<dim_t, dim_t>>;

  ///
  /// @brief The jump deltas for a knight.
  ///
  static const jump_list JUMP_KNIGHT;

  ///
  /// @brief The jump deltas for a king.
  ///
  static const jump_list JUMP_KING;

  ///
  /// @brief Default constructor.
  /// @detail Initializes a board with the standard number of pieces, with
  /// white's turn to move.
  ///
  Board();

  ///
  /// @brief Default copy constructor.
  /// @param board The @c Board being copied.
  ///
  Board(const Board &board) = default;

  ///
  /// @brief Default move constructor.
  /// @param board The @c Board being moved.
  ///
  Board(Board &&board) = default;

  ///
  /// @brief Uses a list of squres to construct board.
  /// @param squareList The list of pieces to put on the board.
  /// @param color The color to move next.
  /// @param boardInfo The @c BoardInfo.
  /// @param lastMove The last move made.
  /// @throw Never throws.
  ///
  Board
    (const std::vector<Square> &squareList,
     const Color color,
     const BoardInfo &boardInfo,
     const PieceMove &lastMove = PieceMove());

  ///
  /// @brief Default copy assignment.
  /// @param board The @c Board being copied.
  ///
  Board&
  operator=(const Board &board) = default;

  ///
  /// @brief Default move assignment.
  /// @param board The @c Board being moved.
  ///
  Board&
  operator=(Board &&board) = default;

  ///
  /// @brief Default move destructor.
  /// @throw Never throws.
  ///
  ~Board() noexcept = default;

  ///
  /// @brief Determine if position is within bounds of board.
  /// @param position The position in question.
  /// @return True if position is within bounds of board.
  /// @throw Never throws.
  ///
  static bool
  isInBound(dim_t position) noexcept;

  ///
  /// @brief Determine if row and column are in bounds.
  /// @param row The row of the position.
  /// @param column The column of the position.
  /// @return True if position is within bounds of board.
  /// @throw Never throws.
  ///
  static bool
  isInBound(dim_t row, dim_t column) noexcept;

  ///
  /// @brief Determine if the king whose turn is it to move can do short castling.
  /// @return True if the king can do short castling.
  /// @throw Never throws.
  ///
  bool
  canCastle() const noexcept;

  ///
  /// @brief Determine if the king whose turn is it to move can do long castling.
  /// @return True if the king can do long castling.
  /// @throw Never throws.
  ///
  bool
  canCastleLong() const noexcept;

  ///
  /// @brief Return a vector of all the legal moves from the given position.
  /// @param row The row in the board.
  /// @param col The column in the board.
  /// @return A vector of all the legal moves from the current position. An empty
  /// vector if there are no moves from the given position.
  ///
  std::vector<PieceMove>
  getMoves(dim_t row, dim_t col) const;

  ///
  /// @brief Return a vector of all the legal moves from all the pieces on the board.
  /// @param row The row in the board.
  /// @param col The column in the board.
  /// @return A vector of all the legal moves from the all the pieces on the board.
  /// An empty vector if there are no moves from the given position.
  ///
  std::vector<PieceMove>
  getMoves() const;

  ///
  /// @brief Return a vector of all the boards that can be reached from this board in
  /// one move.
  /// @detail If there are no legal moves, then the vector of boards will be empty.
  /// This may mean that the current position is a checkmate, a stalemate, or that
  /// there are no pieces on the board.
  /// @return A vector of all the legal moves from the current position.
  ///
  std::vector<Board>
  getBoards() const;

  ///
  /// @brief Make a move and return a new board.
  /// @detail Meant to be used to take a board to a position.
  /// @detail Does not affect the state of this board.
  /// @param pieceMove The @c PieceMove.
  /// @return A copy of the new @c Board after the move.
  /// @TODO throw exception if the move is not legal (ChessError)
  ///
  Board
  makeMoveCopy(const PieceMove &pieceMove) const;

  ///
  /// @brief Make a move on the current board.
  /// @detail This move will become the new last move. Meant to be used to take a
  /// board to a position.
  /// @param pieceMove The @c PieceMove.
  /// @return A reference to this @c Board.
  /// @throw Never throws.
  /// @TODO throw exception if the move is not legal (ChessError)
  ///
  Board&
  makeMove(const PieceMove &pieceMove);

  ///
  /// @brief Get the last move made on this board.
  /// @return A copy of the last move.
  /// @throw Never throws.
  ///
  PieceMove
  lastMove() const noexcept;

  ///
  /// @brief Check if the last move is valid, given the current position.
  /// @return True if the last move is valid, false otherwise.
  /// @throw Never throws.
  ///
  bool
  isLastMoveOk() const noexcept;

  ///
  /// @brief Get the contents of a @c Square at a given row and column.
  /// @param row The row of the @c Board.
  /// @param column The column of the @c Board.
  /// @return A copy of the @c Square at the specified row and column.
  /// @throw Never throws.
  ///
  Square
  operator()(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Provide an iterator to the first @c Square in the @c Board.
  /// @detail The iterator cannot modify the @c Board.
  /// @return An iterator to the first @c Square.
  /// @throw Never throws.
  ///
  const_iterator
  begin() const noexcept;

  ///
  /// @brief Provide an iterator to one past the last @c Square in the @c Board.
  /// @return An iterator to one past the last @c Square in the board.
  /// @throw Never throws.
  ///
  const_iterator
  end() const noexcept;

  ///
  /// @brief Get a list of jump positions that are legal from a given row and column.
  /// @param row The row where the jump is being made from.
  /// @param column The column where the jump is being made from.
  /// @return positions The list of jumping positions.
  /// @throw Never throws.
  ///
  jump_list
  jump(dim_t row, dim_t column, const jump_list &positions) const;

  ///
  /// @brief Determine if there is a pawn check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  /// @throw Never throws.
  ///
  bool
  isCheckPawn(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Determine if there is a knight check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  ///
  bool
  isCheckKnight(dim_t row, dim_t column) const;

  ///
  /// @brief Determine if there is a bishop check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  /// @throw Never throws.
  ///
  bool
  isCheckBishop(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Determine if there is a rook check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  /// @throw Never throws.
  ///
  bool
  isCheckRook(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Determine if there is a queen check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  /// @throw Never throws.
  ///
  bool
  isCheckQueen(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Determine if there is a king check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  ///
  bool
  isCheckKing(dim_t row, dim_t column) const;

  ///
  /// @brief Determine if there is a check at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return True if there is a check at the given square.
  ///
  bool
  isCheck(dim_t row, dim_t column) const;

  ///
  /// @brief Determine if there is an en passant at a given column.
  /// @param color The @c Color.
  /// @param toColumn The column where there might be an en passant.
  /// @return True if there is an en passant at the given column.
  /// @throw Never throws.
  ////
  bool
  isEnPassant(Color color, dim_t toColumn) const noexcept;

  ///
  /// @brief Move the pawn at the given row and column.
  /// @param row The row where the pawn is located.
  /// @param column The column where the pawn is located.
  /// @return A vector of moves.
  ///
  std::vector<PieceMove>
  movePawn(dim_t row, dim_t column) const;

  ///
  /// @brief Move the knight at the given row and column.
  /// @param row The row where the knight is located.
  /// @param column The column where the knight is located.
  /// @return A vector of squares where the knight can move.
  ///
  std::vector<PieceMove>
  moveKnight(dim_t row, dim_t column) const;

  ///
  /// @brief Move the bishop at the given row and column.
  /// @param row The row where the bishop is located.
  /// @param column The column where the bishop is located.
  /// @return A vector of squares where the bishop can move.
  ///
  std::vector<PieceMove>
  moveBishop(dim_t row, dim_t column) const;

  ///
  /// @brief Move the rook at the given row and column.
  /// @param row The row where the rook is located.
  /// @param column The column where the rook is located.
  /// @return A vector of squares where the rook can move.
  ///
  std::vector<PieceMove>
  moveRook(dim_t row, dim_t column) const;

  ///
  /// @brief Move the queen at the given row and column.
  /// @param row The row where the queen is located.
  /// @param column The column where the queen is located.
  /// @return A vector of squares where the queen can move.
  ///
  std::vector<PieceMove>
  moveQueen(dim_t row, dim_t column) const;

  ///
  /// @brief Move the king at the given row and column.
  /// @param row The row where the king is located.
  /// @param column The column where the king is located.
  /// @return A vector of squares where the king can move.
  ///
  std::vector<PieceMove>
  moveKing(dim_t row, dim_t column) const;

  ///
  /// @brief Return string representation of the board.
  /// @return A string representing the board.
  ///
  std::string
  toString() const;

  ///
  /// @brief Get the hash code for this board.
  /// @details Hashes the raw contents of the board and the color reprsenting whose
  /// turn is it to move, which are also the two characteristics used to determine
  /// equality. Implemented using One-at-a-Time hash
  /// @return The numeric hash code for this board.
  ///
  size_t
  hashCode() const noexcept;

  ///
  /// @brief Get the color of whose turn it is to move.
  /// @return The color of the player whose turn it is to move.
  ///
  Color
  colorToMove() const noexcept;

private:
  ///
  /// @brief Make a move on a new board.
  /// @detail Does not affect state of this board.
  /// @param pieceMove The @c PieceMove.
  /// @return A copy of the board after the move.
  ///
  Board
  moveCopy(const PieceMove &pieceMove) const;

  ///
  /// @brief Make a move on the board.
  /// @detail The move becomes the last move made.
  /// @param pieceMove The @c PieceMove.
  /// @return A reference to this @c Board.
  /// @throw Never throws.
  ///
  Board&
  moveRef(const PieceMove &pieceMove) noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the diagonal up and to the right.
  /// @detail Can use this to determine if there is a check from a bishop or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckNE(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the diagonal down and to the right.
  /// @detail Can use this to determine if there is a check from a bishop or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool isCheckSE(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the diagonal down and to the left.
  /// @detail Can use this to determine if there is a check from a bishop or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckSW(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a  check at the given row and column from a piece
  /// in the diagonal up and to the left.
  /// @detail Can use this to determine if there is a check from a bishop or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckNW(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the column from above.
  /// @detail Can use this to determine if there is a check from a rook or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckN(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the row from the right.
  /// @detail Can use this to determine if there is a check from a rook or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckE(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the column from below.
  /// @detail Can use this to determine if there is a check from a rook or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckS(dim_t row, dim_t column, Piece piece) const noexcept;

  ///
  /// @brief Determine if there is a check at the given row and column from a piece
  /// in the row from the left.
  /// @detail Can use this to determine if there is a check from a rook or a queen.
  /// @param row The row where the king might be located.
  /// @param column The column where the king might be located.
  /// @return True if there is a check.
  /// @throw Never throws.
  ///
  bool
  isCheckW(dim_t row, dim_t column, Piece piece) const noexcept;

  // The underlying board.
  BasicBoard mBoard;

  // Indicates the player's turn: either white or black moves.
  Color mColor;

  // The last move on the board.
  PieceMove mLastMove;

  //
  // @brief Maintains information about that may limit the moves a king can make.
  // @details Knows if a king or any of the rooks have moved, and if either king is
  // in check or if it's mate for one of them.
  //
  BoardInfo mInfo;

}; // Board

///
/// @brief Writes the current board position to an output stream.
/// @param os The output stream.
/// @param board The board.
/// @return The output stream.
///
std::ostream&
operator<<(std::ostream &os, const Board &board);

///
/// @brief Equality operator.
/// @detail The board position, and who's turn is it to play determine the uniqueness
/// of a board, and whether two boards are equal or not. Therefore, it is enough to
/// look the eight rows and who's turn it is.
/// @param board1 The first board.
/// @param board2 The second board.
/// @return True if boards are equal, false otherwise.
/// @except Guaranteed not to throw an exception.
///
bool
operator==(const Board &boar1, const Board &board2) noexcept;

///
/// @brief Non-equality operator.
/// @detail The board position, and who's turn is it to play determine the uniqueness
/// of a board, and whether two boards are equal or not. Therefore, it is enough to
/// look the eight rows and who's turn it is.
/// @param board1 The first board.
/// @param board2 The second board.
/// @return False if boards are equal, true otherwise.
/// @except Guaranteed not to throw an exception.
///
bool
operator!=(const Board &boar1, const Board &board2) noexcept;

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

//
// check if position is valid in board
//
inline bool
Board::isInBound(dim_t position) noexcept
{
  return position >= 0 && position < BOARD_DIM;
}

//
// check if row and column are within bounds of board
//
inline bool
Board::isInBound(dim_t row, dim_t column) noexcept
{
  return row >= 0 && column < BOARD_DIM
      && column >= 0 && column < BOARD_DIM;
}

//
// make a move on a copy of the board
//
inline Board
Board::makeMoveCopy(const PieceMove &pieceMove) const
{
  Board board(*this);
  board.makeMove(pieceMove);

  return board;
}

//
// get the last move
//
inline PieceMove
Board::lastMove() const noexcept
{
  return mLastMove;
}

//
// get a square from a board
//
inline Square
Board::operator()(dim_t row, dim_t column) const noexcept
{
  assert(isInBound(row, column));
  return Square(row, column, get(row, column));
}

//
// iterator to the first square
//
inline Board::iterator
Board::begin() const noexcept
{
  return iterator(*this);
}

//
// iterator to one past the last square
//
inline Board::iterator
Board::end() const noexcept
{
  return iterator(*this, 0);
}

//
// obtain a string representation of this board
//
inline std::string
Board::toString() const
{
  std::ostringstream oss;
  oss << *this;

  return oss.str();
}

//
// determine whether it is white's or black's turn to move
//
inline Color
Board::colorToMove() const noexcept
{
  return mColor;
}

//
// get a copy of the board after making a move
//
inline Board
Board::moveCopy(const PieceMove &pieceMove) const
{
  Board board(*this);
  board.moveRef(pieceMove);
  return board;
}

//
// compare boards for equality
// TODO: also compare mInfo, because two boards may have the same position, but
// the kings and rooks may be able to make different moves. Also change how the
// hash code is computed, so that it takes mInfo into account.
//
inline bool
operator==(const Board &board1, const Board &board2) noexcept
{
  return board1.mColor == board2.mColor
      && std::equal(board1.begin(), board1.end(), board2.begin());
}

//
// compare boards for non-equality
//
inline bool
operator!=(const Board &board1, const Board &board2) noexcept
{
  return !(board1 == board2);
}

} // namespace zoor

namespace std {

///
/// @brief Board specialization for <em>hash</em>. Needs to be defined within std
/// namespece.
///
template<>
struct hash<zoor::Board>
{
  using argument_type = zoor::Board;
  using result_type = size_t;

  result_type
  operator()(const argument_type& arg)
  {
    return arg.hashCode();
  }
};

} // std
#endif 
