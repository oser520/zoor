/**
 * @file piecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-04
 */

#include <string>
#include <iostream>
#include <utility>
#include <cassert>

#include "piecemoves.hh"

namespace zoor {

using dim_type = PieceMoves::dim_type;
using iterator = PieceMoves::iterator;
using const_iterator = PieceMoves::const_iterator;
using size_type = PieceMoves::size_type;

PieceMoves::PieceMoves(const Square &square) noexcept
  : mSquare(square)
{
  assert(mSquara.piece() != PieceCode::NONE);
  assert(mSquara.color() != PieceColor::NONE);
}

PieceMoves::PieceMoves(Square &&square) noexcept
  : mSquare(std::move(square))
{
  assert(mSquara.piece() != PieceCode::NONE);
  assert(mSquara.color() != PieceColor::NONE);
}

PieceMoves::PieceMoves
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mSquare(row, column, piece, color)
{
  assert(piece != PieceCode::NONE);
  assert(color != PieceColor::NONE);
}



} // namespace zoor
