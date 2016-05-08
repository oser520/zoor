/////////////////////////////////////////////////////////////////////////////////////
/// @file piecemoves.cc
/// @author Omar A Serrano
/// @date 2016-01-04
/////////////////////////////////////////////////////////////////////////////////////

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
#include "piececode.hh"
#include "piecemove.hh"
#include "square.hh"

namespace zoor {

//
// default ctor
//
PieceMove::PieceMove() noexcept
  : mCastleInfo(0) {}

//
// four param ctro
//
PieceMove::PieceMove
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mFrom(row, column, piece, color),
    mCastleInfo(0) {}

//
// three param ctro
//
PieceMove::PieceMove(dim_type row, dim_type column, piececode_t code) noexcept
  : mFrom(row, column, code),
    mCastleInfo(0) {}

//
// five param ctro
//
PieceMove::PieceMove
  (dim_type fromRow,
   dim_type fromColumn,
   piececode_t code,
   dim_type toRow,
   dim_type toColumn) noexcept
  : mFrom(fromRow, fromColumn, code),
    mPromo(toRow, toColumn),
    mCastleInfo(0) {}

//
// source piece setter
//
PieceMove&
PieceMove::setPiece
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mFrom.setLocation(row, column).setPiece(piece).setColor(color);
  return *this;
}

//
// source piece setter
//
PieceMove&
PieceMove::setPiece(dim_type row, dim_type column, piececode_t code) noexcept
{
  mFrom.setLocation(row, column).setPieceCode(code);
  return *this;
}

//
// source piece setter
//
PieceMove&
PieceMove::setPiece(PieceCode piece, PieceColor color) noexcept
{
  mFrom.setPiece(piece).setColor(color);
  return *this;
}

//
// source piece setter
//
PieceMove&
PieceMove::setPiece(piececode_t code) noexcept
{
  mFrom.setPieceCode(code);
  return *this;
}

//
// capture setter
//
PieceMove&
PieceMove::setCapture
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mCapture.setLocation(row, column).setPiece(piece).setColor(color);
  return *this;
}

//
// capture setter
//
PieceMove&
PieceMove::setCapture(dim_type row, dim_type column, piececode_t code) noexcept
{
  mCapture.setLocation(row, column).setPieceCode(code);
  return *this;
}

//
// capture setter
//
PieceMove&
PieceMove::setCapture(PieceCode piece, PieceColor color) noexcept
{
  mCapture.setPiece(piece).setColor(color);
  return *this;
}

//
// capture setter
//
PieceMove&
PieceMove::setCapture(piececode_t code) noexcept
{
  mCapture.setPieceCode(code);
  return *this;
}

//
// does move result in a capture
//
bool
PieceMove::isCapture() const noexcept
{
  return mCapture.piece() != PieceCode::NONE;
}

//
// promotion setter
//
PieceMove&
PieceMove::setPromo
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mPromo.setLocation(row, column).setPiece(piece).setColor(color);
  return *this;
}

//
// promotion setter
//
PieceMove&
PieceMove::setPromo
  (dim_type row,
   dim_type column,
   piececode_t code) noexcept
{
  mPromo.setLocation(row, column).setPieceCode(code);
  return *this;
}

//
// promotion setter
//
PieceMove&
PieceMove::setPromo(PieceCode piece, PieceColor color) noexcept
{
  mPromo.setPiece(piece).setColor(color);
  return *this;
}

//
// promotion setter
//
PieceMove&
PieceMove::setPromo(piececode_t code) noexcept
{
  mPromo.setPieceCode(code);
  return *this;
}

//
// to row setter
//
PieceMove&
PieceMove::setToRow(dim_type row) noexcept
{
  mPromo.setRow(row);
  return *this;
}

//
// to column setter
//
PieceMove&
PieceMove::setToColumn(dim_type column) noexcept
{
  mPromo.setColumn(column);
  return *this;
}

//
// to row and to column setter
//
PieceMove&
PieceMove::setGoTo(dim_type row, dim_type column) noexcept
{
  mPromo.setLocation(row, column);
  return *this;
}

//
// setup the move for short castling
//
PieceMove&
PieceMove::doCastle(PieceColor color) noexcept
{
  auto row = isWhite(color) ? 0 : 7;
  setPiece(row, 4, PieceCode::KING, color);
  setPromo(row, 6, 0);
  setCapture(0, 0, 0);
  mCastleInfo = 0x1;

  return *this;
}
//
// setup the move for long castling
//
PieceMove&
PieceMove::doCastleLong(PieceColor color) noexcept
{
  auto row = isWhite(color) ? 0 : 7;
  setPiece(row, 4, PieceCode::KING, color);
  setPromo(row, 2, 0);
  setCapture(0, 0, 0);
  mCastleInfo = 0x2;

  return *this;
}

//
// check if the move represents short castling
//
inline bool
PieceMove::isCastle() const noexcept
{
  return isKing(mFrom.piece())
      && isRook(mOther.piece())
      && mFrom.color() == mOther.color()
      && mTo.row() == 6;
}

//
// check if the move represents long castling
//
inline bool
PieceMove::isCastleLong() const noexcept
{
  return isKing(mFrom.piece())
      && isRook(mOther.piece())
      && mFrom.color() == mOther.color()
      && mTo.row() == 2;
}

//
// check if the move is en passant
//
bool
PieceMove::isEnPassant() const noexcept
{
  return isPawn(mFrom.piece())
      && isPawn(mCapture.piece())
      && mCapture.row() != mPromo.row();
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
  hsh = hsh * 486187739 + mPromo.hashCode();
  hsh = hsh * 486187739 + mCapture.hashCode();

  return hsh;
}

//
// are moves equal
//
bool
operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return pm1.mFrom == pm2.mFrom
      && pm1.mPromo == pm2.mPromo
      && pm1.mCapture == pm2.mCapture;
}

//
// output stream
//
std::ostream&
operator<<(std::ostream &os, const PieceMove &pm)
{
  os << "("
     << pm.mFrom << ", "
     << pm.mPromo << ", "
     << pm.mCapture << ")";
  return os;
}

} // namespace zoor
