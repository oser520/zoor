////////////////////////////////////////////////////////////////////////////////
//! @file pawnmove.hh
//! @author Omar A Serrano
//! @date 2016-09-04
////////////////////////////////////////////////////////////////////////////////
#ifndef _PAWNMOVE_H
#define _PAWNMOVE_H

//
// STL
//
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

//! Represents the moves a pawn can make from a given position on a board.
class PawnMove
{
  dim_t mRow;
  dim_t mCol;
  const Board &mBoard;
  Color mColor;
  std::vector<std::pair<dim_t, dim_t>> mDeltas; 

public:
  //! Initializes PawnMove with the row and column of the pawn, and the board.
  //! @param row The row of the pawn.
  //! @param col The column of the pawn.
  //! @param board The board where the pawn is located.
  PawnMove(dim_t row, dim_t col, const Board &board) noexcept;

  //! @return The color of the pawn.
  Color
  color() const noexcept;

  //! @return The row of the pawn.
  dim_t
  row() const noexcept;

  //! @return The board.
  const Board&
  board() const noexcept;

  //! Changes the square from where the pawn is moving.
  //! @param row The new row location of the pawn.
  //! @param column The new column location of the pawn.
  //! @throw If the square does not contain a pawn.
  void
  square(dim_t row, dim_t col);
  
  //! Determine if the piece can move to the given square.
  //! @param row The row where the pawn should move.
  //! @param row The column where the pawn should move.
  //! @return True if the pawn can move to the square, false otherwise.
  bool
  canMove(dim_t row, dim_t col) const noexcept;

  //! Moves the pawn to the given square.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return A PieceMove.
  //! @throw If the pawn cannot move to the given square.
  PieceMove
  move(dim_t row, dim_t col) const;

  //! Moves the pawn to the given square.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return A PieceMove.
  //! @throw If the pawn cannot move to the given square.
  std::vector<PieceMove>
  moves() const;

private:
  //! Moves the pawn to the given square.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return A PieceMove.
  PieceMove
  _move(dim_t row, dim_t col) const;

  //! Checks if the given move is a pawn promotion.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return True if the move is a pawn promotion, false otherwise.
  bool
  isPromotion(dim_t row, dim_t col) const noexcept;

  //! Promotes the pawn to the given square.
  //! @param row The promotion row.
  //! @param col The promotion column.
  //! @return A vector of PieceMoves representing pawn promotions.
  //! @throw May throw a memory allocation failure.
  std::vector<PieceMove>
  promote(dim_t row, dim_t col) const;

  //! Checks if the pawn can move to the given square.
  //! @details The row and column are valid, but this checks that
  //! the square does not contain a piece of the same color, or if
  //! the move is diagonal, that the square contains an enemy piece,
  //! or if the move is an en passant, that the requirements for
  //! en passant be met.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return True if the pawn can move to the square, false otherwise.
  bool
  _canMove(dim_t row, dim_t col) const noexcept;

  //! @return True if this is the pawn's first move, false otherwise.
  bool
  isFirstMove() const noexcept;

  //! @return The row and column two squares ahead of the pawn.
  std::pair<dim_t, dim_t>
  jumpTwo() const noexcept;

  //! Checks the move to the given square is an en passant move.
  //! @param row The row of the square.
  //! @param col The column of the square.
  //! @return True if the move is en passant, false otherwise.
  bool
  isEnPassant(dim_t row, dim_t col) const noexcept;

  //! Does an en passant move to the given square.
  //! @param row The row of the square.
  //! @param col The column of the square.
  //! @return An en passant PieceMove.
  PieceMove
  enPassant(dim_t row, dim_t col) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

} // namespace zoor
#endif // _PAWNMOVE_H
