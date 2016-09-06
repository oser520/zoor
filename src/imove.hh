////////////////////////////////////////////////////////////////////////////////
//! @file imove.hh
//! @author Omar A Serrano
//! @date 2016-09-06
////////////////////////////////////////////////////////////////////////////////
#ifndef _IMOVE_H
#define _IMOVE_H

//
// STL
//
#include <cassert>
#include <vector>

//
// zoor
//
#include "basictypes.hh"

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

namespace zoor {

class Board;
class PieceMove;

//! Represents the moves a piece can make from a given position on a board.
class IMove
{
  dim_t mRow;
  dim_t mCol;
  const Board &mBoard;
  Color mColor;

public:
  //! Initializes IMove with the row and column of the piece, and the board
  //! where the piece is moving.
  //! @param row The row of the piece.
  //! @param col The column of the piece.
  //! @param board The board where the piece is moving.
  IMove(dim_t row, dim_t col, const Board &board);

  //! Virtual dtor.
  virtual
  ~IMove() noexcept = default;

  //! @return The board where the piece is moving.
  const Board&
  board() const noexcept;

  //! @return The color of the piece.
  Color
  color() const noexcept;

  //! @return The row of the piece.
  dim_t
  row() const noexcept;

  //! @return The column of the piece.
  dim_t
  col() const noexcept;

  //! Changes the square from where the piece is moving.
  //! @param row The new row location of the piece.
  //! @param column The new column location of the piece.
  //! @throw If the square does not contain the same piece, or the piece is not
  //! the same color.
  void
  square(dim_t row, dim_t col);

  //! @return The type of piece making the move.
  virtual constexpr Piece
  type() const noexcept;

  //! Determine if the piece can move to the given square.
  //! @param row The row where the piece should move.
  //! @param row The column where the piece should move.
  //! @return True if the piece can move to the square, false otherwise.
  virtual bool
  canMove(dim_t row, dim_t col) const noexcept;

  //! Moves the piece to the given square.
  //! @param row The row of the square where the piece is moving.
  //! @param col The column of the square where the piece is moving.
  //! @return A PieceMove.
  //! @throw If the piece cannot move to the given square.
  virtual PieceMove
  move(dim_t row, dim_t col) const;

  //! The list of moves the piece can make.
  //! @return A list of moves.
  //! @throw If there is a bad memory allocation.
  virtual std::vector<PieceMove>
  moves() const;
};

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

IMove::IMove(dim_t row, dim_t col, const Board &board)
  : mRow(row),
    mCol(col),
    mBoard(board),
    mColor(mBoard(mRow, mCol).color())
{
  // TODO: return exception instead of asserting
  assert(isColor(mColor));
  assert(mColor == mBoard.nextTurn());
}

inline const Board&
IMove::board() const noexcept
{
  return mBoard;
}

inline Color
IMove::color() const noexcept
{
  return mColor;
}

inline dim_t
IMove::row() const noexcept
{
  return mRow;
}

inline dim_t
IMove::col() const noexcept
{
  return mCol;
}

inline void
IMove::square(dim_t row, dim_t col)
{
  // TODO: return exception instead of asserting
  assert(mBoard(row, col).piece() == type());
  assert(mBoard(row, col).color() == color());
  mRow = row;
  mCol = col;
}

} // namespace zoor
#endif // _IMOVE_H
