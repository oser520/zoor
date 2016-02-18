/**
 * @file piecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-04
 */

#include <iostream>
#include <utility>
#include <cassert>

#include "piecemove.hh"
#include "piececode.hh"
#include "square.hh"

namespace zoor {

using dim_type = PieceMove::dim_type;

// four param ctro
PieceMove::PieceMove
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mFrom(row, column, piece, color) {}

// three param ctro
PieceMove::PieceMove(dim_type row, dim_type column, piececode_t code) noexcept
  : mFrom(row, column, code) {}

// five param ctro
PieceMove::PieceMove
  (dim_type fromRow,
   dim_type fromColumn,
   piececode_t code,
   dim_type toRow,
   dim_type toColumn) noexcept
  : mFrom(fromRow, fromColumn, code), mPromo(toRow, toColumn) {}

// from row getter
dim_type PieceMove::fromRow() const noexcept
{
  return mFrom.row();
}

// from column getter
dim_type PieceMove::fromColumn() const noexcept
{
  return mFrom.column();
}

// the row getter for the destination row
dim_type PieceMove::toRow() const noexcept
{
  return mPromo.row();
}

// the column getter for the destination column
dim_type PieceMove::toColumn() const noexcept
{
  return mPromo.column();
}

// the row getter for the captured piece
dim_type PieceMove::captureRow() const noexcept
{
  return mCapture.row();
}

// the column getter for the captured piece
dim_type PieceMove::captureColumn() const noexcept
{
  return mCapture.column();
}

// source piece setter
PieceMove& PieceMove::setPiece
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mFrom.setRow(row)
       .setColumn(column)
       .setPiece(piece)
       .setColor(color);
  return *this;
}

// source piece setter
PieceMove&
PieceMove::setPiece(dim_type row, dim_type column, piececode_t code) noexcept
{
  mFrom.setLocation(row, column).setPieceCode(code);
  return *this;
}

// source piece setter
PieceMove&
PieceMove::setPiece(PieceCode piece, PieceColor color) noexcept
{
  mFrom.setPiece(piece).setColor(color);
  return *this;
}

// source piece setter
PieceMove& PieceMove::setPiece(piececode_t code) noexcept
{
  mFrom.setPieceCode(code);
  return *this;
}

// source square getter
Square PieceMove::fromSquare() const noexcept
{
  return mFrom;
}

// source piece getter
PieceCode PieceMove::fromPiece() const noexcept
{
  return mFrom.piece();
}

// source piece color getter
PieceColor PieceMove::fromColor() const noexcept
{
  return mFrom.color();
}

// capture setter
PieceMove& PieceMove::setCapture
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mCapture.setRow(row)
          .setColumn(column)
          .setPiece(piece)
          .setColor(color);
  return *this;
}

// capture setter
PieceMove&
PieceMove::setCapture(dim_type row, dim_type column, piececode_t code) noexcept
{
  mCapture.setLocation(row, column).setPieceCode(code);
  return *this;
}

// capture setter
PieceMove&
PieceMove::setCapture(PieceCode piece, PieceColor color) noexcept
{
  mCapture.setPiece(piece).setColor(color);
  return *this;
}

// capture setter
PieceMove& PieceMove::setCapture(piececode_t code) noexcept
{
  mCapture.setPieceCode(code);
  return *this;
}

// does move result in a capture
bool PieceMove::isCapture() const noexcept
{
  return mCapture.piece() != PieceCode::NONE;
}

// get the captured square
Square PieceMove::captureSquare() const noexcept
{
  return mCapture;
}

// get the captured piece
PieceCode PieceMove::capturePiece() const noexcept
{
  return mCapture.piece();
}

// get the captured piece's color
PieceColor PieceMove::captureColor() const noexcept
{
  return mCapture.color();
}

// promotion setter
PieceMove& PieceMove::setPromo
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mPromo.setRow(row)
        .setColumn(column)
        .setPiece(piece)
        .setColor(color);
  return *this;
}

// promotion setter
PieceMove& PieceMove::setPromo
  (dim_type row,
   dim_type column,
   piececode_t code) noexcept
{
  mPromo.setLocation(row, column).setPieceCode(code);
  return *this;
}

// promotion setter
PieceMove&
PieceMove::setPromo(PieceCode piece, PieceColor color) noexcept
{
  mPromo.setPiece(piece).setColor(color);
  return *this;
}

// promotion setter
PieceMove& PieceMove::setPromo(piececode_t code) noexcept
{
  mPromo.setPieceCode(code);
  return *this;
}

// does move result in promotion
bool PieceMove::isPromo() const noexcept
{
  return mPromo.piece() != PieceCode::NONE;
}

// promotion square
Square PieceMove::promoSquare() const noexcept
{
  return mPromo;
}

// promotion piece getter
PieceCode PieceMove::promoPiece() const noexcept
{
  return mPromo.piece();
}

// promotion piece color getter
PieceColor PieceMove::promoColor() const noexcept
{
  return mPromo.color();
}

// to row setter
PieceMove& PieceMove::setToRow(dim_type row) noexcept
{
  mPromo.setRow(row);
  return *this;
}

// to column setter
PieceMove& PieceMove::setToColumn(dim_type column) noexcept
{
  mPromo.setColumn(column);
  return *this;
}

// to row and to column setter
PieceMove& PieceMove::setGoTo(dim_type row, dim_type column) noexcept
{
  mPromo.setLocation(row, column);
  return *this;
}

// check if the move results in mate
bool PieceMove::isMate() const noexcept
{
  return isKing(mCapture.piece());
}

// are moves equal
bool operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return pm1.mFrom == pm2.mFrom
      && pm1.mPromo == pm2.mPromo
      && pm1.mCapture == pm2.mCapture;
}

// are moves different
bool operator!=(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return !(pm1 == pm2);
}

// output stream
std::ostream& operator<<(std::ostream &os, const PieceMove &pm)
{
  os << "("
     << pm.mFrom << ", "
     << pm.mPromo << ", "
     << pm.mCapture << ")";
  return os;
}

} // namespace zoor
