////////////////////////////////////////////////////////////////////////////////
//! @file pawnmove.cc
//! @author Omar A Serrano
//! @date 2016-09-09
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <vector>
#include <utility>
#include <stdexcept>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "pawnmove.hh"
#include "piecemove.hh"

namespace zoor {

PawnMove::PawnMove(dim_t row, dim_t col, const Board &board) noexcept
  : IMove(row, col, board)
{
  assert(isPawn(mBoard(row, col).piece()));
}

constexpr Piece
PawnMove::type() const noexcept
{
  return Piece::P;
}

bool
PawnMove::canMove(dim_t row, dim_t col) const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

PieceMove
PawnMove::move(dim_t row, dim_t col) const
{
  throw std::logic_error("NOT IMPLEMENTED");
}

std::vector<PieceMove>
PawnMove::moves() const
{
  throw std::logic_error("NOT IMPLEMENTED");
}

PieceMove
PawnMove::_move(dim_t row, dim_t col) const
{
  throw std::logic_error("NOT IMPLEMENTED");
}

bool
PawnMove::isPromotion(dim_t row, dim_t col) const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

std::vector<PieceMove>
PawnMove::promote(dim_t row, dim_t col) const
{
  throw std::logic_error("NOT IMPLEMENTED");
}

bool
PawnMove::_canMove(dim_t row, dim_t col) const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

bool
PawnMove::isFirstMove() const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

std::pair<dim_t, dim_t>
PawnMove::jumpTwo() const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

bool
PawnMove::isEnPassant(dim_t row, dim_t col) const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

PieceMove
PawnMove::enPassant(dim_t row, dim_t col) const noexcept
{
  throw std::logic_error("NOT IMPLEMENTED");
}

} // namespace zoor
