/**
 * @file square.cc
 * @author Omar A Serrano
 * @data 2015-12-31
 */

#include <iostream>
#include <cassert>

#include "square.hh"

namespace zoor {

using dim_type = Square::dim_type;

Square::Square(dim_type row, dim_type column) noexcept
  : mRow(row),
    mColum(column)
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
    mColum(column)
{
  assert(mRow < BOARD_DIM);
  assert(mColumn < BOARD_DIM);
}

dim_type Square::row() const noexcept
{
  return mRow;
}

dim_type Square::col() const noexcept
{
  return mColumn;
}

Square& Square::setRow(dim_type row) noexcept
{
  assert(row < BOARD_DIM);
  mRow = row;
  return *this;
}

Square& Square::setCol(dim_type column) noexcept
{
  assert(column < BOARD_DIM);
  mColumn = column;
  return *this;
}

bool operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.mRow == square2.mRow && square1.mColumn == square2.mColumn;
}

bool operator!=(const Square& square1, const Square& square2) noexcept;
{
  return !(square1 == square2);
}

std::ostream& operator<<(std::ostream& os, const Square& square)
{
  os << "(" << square.mRow << ", " << square.mColumn << ")";
  return os;
}

} // namespace zoor
