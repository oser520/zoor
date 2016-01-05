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
#include "piececode.hh"

namespace zoor {

using dim_type = PieceMoves::dim_type;
using iterator = PieceMoves::iterator;
using const_iterator = PieceMoves::const_iterator;
using size_type = PieceMoves::size_type;

PieceMoves::PieceMoves(const Square &square) noexcept
  : mSquare(square)
{
  assert(piece() != PieceCode::NONE);
  assert(color() != PieceColor::NONE);
}

PieceMoves::PieceMoves(Square &&square) noexcept
  : mSquare(std::move(square))
{
  assert(piece() != PieceCode::NONE);
  assert(color() != PieceColor::NONE);
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

PieceMoves& PieceMoves::setPiece(PieceCode piece) noexcept
{
  if (piece() != piece) {
    mSquare.setPiece(piece);
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setColor(PieceColor color) noexcept
{
  if (color() != color) {
    mSquare.setColor(color);
    if (!empty()) clear();
  }
  return *this;
}

dim_type PieceMoves::row() const noexcept
{
  return mSquare.row();
}

dim_type PieceMoves::column() const noexcept
{
  return mSquare.column();
}

PieceCode PieceMoves::piece() const noexcept
{
  return mSquare.piece();
}

PieceColor PieceMoves::color() const noexcept
{
  return mSquare.color();
}



} // namespace zoor
