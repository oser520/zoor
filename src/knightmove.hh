////////////////////////////////////////////////////////////////////////////////
//! @file knightmove.hh
//! @author Omar A Serrano
//! @date 2016-09-07
////////////////////////////////////////////////////////////////////////////////
#ifndef _KNIGHTMOVE_H
#define _KNIGHTMOVE_H

//
// STL
//
#include <array>
#include <vector>

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

//! Represents the moves a knight can make from a given position on a board.
class KnightMove
  : public IMove
{
  static const std::array<std::pair<dim_t, dim_t>, 8> mDeltas;

public:
  //! @copydoc IMove::IMove(dim_t, dim_t, Board)
  KnightMove(dim_t row, dim_t col, const Board &board) noexcept;

  //! @copydoc IMove::type()
  constexpr Piece
  type() const noexcept override;

  //! @copydoc IMove::canMove(dim_t, dim_t)
  bool
  canMove(dim_t row, dim_t col) const noexcept override;

  //! @copydoc IMove::move(dim_t, dim_t)
  std::vector<PieceMove>
  move(dim_t row, dim_t col) const override;

  //! @copydoc IMove::moves()
  std::vector<PieceMove>
  moves() const override;
};

} // namespace zoor
#endif // _KNIGHTMOVE_H
