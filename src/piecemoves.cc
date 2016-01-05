/**
 * @file piecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-04
 */

#include "piecemoves.hh"

namespace zoor {

using dim_type = PieceMoves::dim_type;
using iterator = PieceMoves::iterator;
using const_iterator = PieceMoves::const_iterator;
using size_type = PieceMoves::size_type;

PieceMoves::PieceMoves(const Square &square)
  : mSquare(square)
{
  assert(mSquara.piece() != PieceCode::NONE);
  assert(mSquara.color() != PieceColor::NONE);
}

PieceMoves::PieceMoves(Square &&square)
  : mSquare(std::move(square))
{
  assert(mSquara.piece() != PieceCode::NONE);
  assert(mSquara.color() != PieceColor::NONE);
}


} // namespace zoor
