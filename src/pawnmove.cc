////////////////////////////////////////////////////////////////////////////////
//! @file pawnmove.cc
//! @author Omar A Serrano
//! @date 2016-09-09
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <array>
#include <vector>
#include <utility>
#include <stdexcept>
#include <cassert>

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
  mDeltas = deltas();
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
  return (isWhite(mColor) && mRow == 1)
      || (isBlack(mColor) && mRow == 6);
}

std::pair<dim_t, dim_t>
PawnMove::jumpTwo() const noexcept
{
  auto col = mCol + 2 * delta();
  return {mRow, col};
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

std::vector<std::pair<dim_t, dim_t>>
PawnMove::deltas() const
{
  auto delta = delta(mColor) + mRow;
  std::array<std::pair<dim_t, dim_t>, 3> arr = {
    {delta, mCol},
    {delta, mCol+1},
    {delta, mCol-1}
  };
  std::vector<std::pair<dim_t, dim_t>> vec;
  for (auto d : arr) {
    if (inBound(d.first, d.second))
      vec.emplace_back(d.first, d.second);
  }
  if (isFirstMove())
    vec.emplace_back(jumpTwo());

  return vec;
}

} // namespace zoor
