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
#include <utility>

//
// zoor
//
#include "basictypes.hh"
#include "imove.hh"

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

namespace zoor {

class Board;
class PieceMove;

//! Represents the moves a pawn can make from a given position on a board.
class PawnMove
  : public IMove
{
  std::vector<std::pair<dim_t, dim_t>> mDeltas;

public:
  //! @copydoc IMove::IMove(dim_t, dim_t, Board)
  PawnMove(dim_t row, dim_t col, const Board &board) noexcept;

  //! @copydoc IMove::type()
  constexpr Piece
  type() const noexcept override;

  //! @copydoc IMove::canMove(dim_t, dim_t)
  bool
  canMove(dim_t row, dim_t col) const noexcept override;

  //! @copydoc IMove::move(dim_t, dim_t)
  PieceMove
  move(dim_t row, dim_t col) const override;

  //! @copydoc IMove::moves()
  std::vector<PieceMove>
  moves() const override;

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

  //! @return A list squares of where it is viable for the pawn to move.
  std::vector<std::pair<dim_t, dim_t>>
  deltas() const;

  //! Checks the move to the given square is an attack move.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return True if the move is an attacking move, false otherwise.
  bool
  isAttack(dim_t row, dim_t col) const noexcept;

  //! Checks the move is a one or two square move forward.
  //! @param row The row of the square where the pawn is moving.
  //! @param col The column of the square where the pawn is moving.
  //! @return True if the move is a move forward, false otherwise.
  bool
  isForward(dim_t row, dim_t col) const noexcept;
};

} // namespace zoor
#endif // _PAWNMOVE_H
