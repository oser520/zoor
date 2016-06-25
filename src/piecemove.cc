////////////////////////////////////////////////////////////////////////////////
//! @file piecemoves.cc
//! @author Omar A Serrano
//! @date 2016-01-04
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

//
// zoor
//
#include "basictypes.hh"
#include "piecemove.hh"
#include "square.hh"

namespace zoor {

//
// four param ctro
//
PieceMove::PieceMove(dim_t row, dim_t column, Piece piece, Color color) noexcept
  : mFrom(row, column, piece, color) {}

//
// three param ctro
//
PieceMove::PieceMove(dim_t row, dim_t column, piece_t code) noexcept
  : mFrom(row, column, code) {}

//
// five param ctro
//
PieceMove::PieceMove
  (dim_t fromRow,
   dim_t fromColumn,
   piece_t code,
   dim_t toRow,
   dim_t toColumn) noexcept
  : mFrom(fromRow, fromColumn, code),
    mTo(toRow, toColumn, code) {}

//
// check if the move represents short castling
//
bool
PieceMove::isCastle() const noexcept
{
  return isKing(sPiece())
      && isRook(xPiece())
      && sColor() == xColor()
      && dColumn() == 6;
}

//
// check if the move represents long castling
//
bool
PieceMove::isCastleLong() const noexcept
{
  return isKing(sPiece())
      && isRook(xPiece())
      && sColor() == xColor()
      && dColumn() == 2;
}

//
// check if the move is en passant
//
bool
PieceMove::isEnPassant() const noexcept
{
  return isPawn(sPiece())
      && isPawn(xPiece())
      && xRow() != dRow();
}

//
// return a string representation of the move
//
std::string
PieceMove::toString() const
{
  std::ostringstream oss;
  oss << *this;

  return oss.str();
}

//
// get the hash code
//
size_t
PieceMove::hashCode() const noexcept
{
  size_t hsh = 17;

  hsh = hsh * 486187739 + mFrom.hashCode();
  hsh = hsh * 486187739 + mTo.hashCode();
  hsh = hsh * 486187739 + mOther.hashCode();

  return hsh;
}

//
// are moves equal
//
bool
operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return pm1.sSquare() == pm2.sSquare()
      && pm1.dSquare() == pm2.dSquare()
      && pm1.xSquare() == pm2.xSquare();
}

//
// output stream
//
std::ostream&
operator<<(std::ostream &os, const PieceMove &pm)
{
  os << "("
     << pm.sSquare() << ", "
     << pm.dSquare() << ", "
     << pm.xSquare() << ")";
  return os;
}

} // namespace zoor
