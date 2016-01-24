/**
 * @file square.cc
 * @author Omar A Serrano
 * @data 2015-12-31
 */

#include <iostream>
#include <cassert>

#include "square.hh"
#include "piececode.hh"

namespace zoor {

using dim_type = Square::dim_type;

Square::Square() noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(),
    mColumn() {}

Square::Square(dim_type row, dim_type column) noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(row),
    mColumn(column)
{
  assert(mRow < BOARD_DIM);
  assert(mColumn < BOARD_DIM);
}

Square::Square
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mPiece(piece),
    mColor(color),
    mRow(row),
    mColumn(column)
{
  assert(mRow < BOARD_DIM);
  assert(mColumn < BOARD_DIM);
}

dim_type Square::row() const noexcept
{
  return mRow;
}

dim_type Square::column() const noexcept
{
  return mColumn;
}

PieceCode Square::piece() const noexcept
{
  return mPiece;
}

PieceColor Square::color() const noexcept
{
  return mColor;
}

Square& Square::setRow(dim_type row) noexcept
{
  assert(row < BOARD_DIM);
  mRow = row;
  return *this;
}

Square& Square::setColumn(dim_type column) noexcept
{
  assert(column < BOARD_DIM);
  mColumn = column;
  return *this;
}

Square& Square::setPiece(PieceCode piece) noexcept
{
  mPiece = piece;
  return *this;
}

Square& Square::setColor(PieceColor color) noexcept
{
  mColor = color;
  return *this;
}

bool operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.mPiece == square2.mPiece
      && square1.mColor == square2.mColor
      && square1.mRow == square2.mRow
      && square1.mColumn == square2.mColumn;
}

bool operator!=(const Square& square1, const Square& square2) noexcept
{
  return !(square1 == square2);
}

std::ostream& operator<<(std::ostream& os, const Square& square)
{
  os << "("
     << square.mPiece << ", "
     << square.mColor << ", "
     << square.mRow << ", "
     << square.mColumn
     << ")";
  return os;
}

} // namespace zoor
