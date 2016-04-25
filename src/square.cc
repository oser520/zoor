/////////////////////////////////////////////////////////////////////////////////////
/// @file square.cc
/// @author Omar A Serrano
/// @data 2015-12-31
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

//
// zoor
//
#include "piececode.hh"
#include "square.hh"

namespace zoor {

using dim_type = Square::dim_type;

//
// default ctor
//
Square::Square() noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(),
    mColumn() {}

//
// two param ctor
//
Square::Square(dim_type row, dim_type column) noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(row),
    mColumn(column)
{
  assert(isInBound(row, column));
}

//
// three param ctor
//
Square::Square(dim_type row, dim_type column, piececode_t code) noexcept
  : mPiece(getPieceCode(code)),
    mColor(getPieceColor(code)),
    mRow(row),
    mColumn(column)
{
  assert(isInBound(row, column));
}

//
// 4 param ctor
//
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
  assert(isInBound(row, column));
}

//
// set the piece and color
//
Square&
Square::setPieceCode(piececode_t code) noexcept
{
  mPiece = getPieceCode(code);
  mColor = getPieceColor(code);
  return *this;
}

//
// set the row and column of the square
//
Square&
Square::setLocation(dim_type row, dim_type column) noexcept
{
  assert(isInBound(row, column));
  mRow = row;
  mColumn = column;
  return *this;
}

//
// get a string representation of the square
//
std::string
Square::toString() const
{
  std::ostringstream oss;
  oss << *this;

  return oss.str();
}

//
// get the hash value for the square
//
size_t
Square::hashCode() const noexcept
{
  // the hash value
  size_t h = 0;

  h += static_cast<size_t>(mPiece);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mColor);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mRow);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mColumn);
  h += h << 10;
  h ^= h >> 6;

  h += h << 3;
  h += h >> 11;
  h += h << 15;

  return h;
}

//
// equality operator
//
bool
operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.mPiece == square2.mPiece
      && square1.mColor == square2.mColor
      && square1.mRow == square2.mRow
      && square1.mColumn == square2.mColumn;
}

//
// non-equality operator
//
bool
operator!=(const Square& square1, const Square& square2) noexcept
{
  return !(square1 == square2);
}

//
// output operator
//
std::ostream&
operator<<(std::ostream& os, const Square& square)
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
