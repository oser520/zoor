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

using dim_type = PieceMoves::dim_type;

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
  : mFrom(fromRow, fromColumn, code), mPromotion(toRow, toColumn) {}

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

// to row getter
dim_type PieceMove::toRow() const noexcept
{
  return mDestination.row();
}

// to column getter
dim_type PieceMove::toColumn() const noexcept
{
  return mDestination.column();
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
  mFrom.setRow(row).setColumn(column).setPieceCode(piece);
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
  mCapture.setRow(row).setColumn(column).setPieceCode(piece);
  return *this;
}

// does move result in a capture
bool PieceMove::isCapture() const noexcept
{
  return mCapture.piece() != PieceCode::NONE;
}

// capture getter
Square PieceMove::capture() const noexcept
{
  return mCapture;
}

// promotion setter
PieceMove& PieceMove::setPromotion
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
{
  mPromotion.setRow(row)
            .setColumn(column)
            .setPiece(piece)
            .setColor(color);
  return *this;
}

// promotion setter
PieceMove& PieceMove::setPromotion
  (dim_type row,
   dim_type column,
   piececode_t code) noexcept
{
  mPromotion.setRow(row)
            .setColumn(column)
            .setPieceCode(piece);
  return *this;
}

// promotion setter
PieceMove&
PieceMove::setPromotion(PieceCode piece, PieceColor color) noexcept
{
  mPromotion.setPiece(piece).setColor(color);
  return *this;
}

// promotion setter
PieceMove& PieceMove::setPromotion(piececode_t code) noexcept
{
  mPromotion.setPieceCode(code);
  return *this;
}

// does move result in promotion
bool PieceMove::isPromotion() const noexcept
{
  return mPromotion.piece() != PieceCode::NONE;
}

// promotion square
Square PieceMove::promotion() const noexcept
{
  return mPromotion;
}

// to row setter
PieceMove& PieceMove::setToRow(dim_type row) noexcept
{
  mPromotion.setRow(row);
  return *this;
}

// to column setter
PieceMove& PieceMove::setToColumn(dim_type column) noexcept
{
  mPromotion.setColumn(column);
  return *this;
}

// to row and to column setter
PieceMove& PieceMove::setDestination(dim_type row, dim_type column) noexcept
{
  mPromotion.setRow(row).setColumn(column);
  return *this;
}

// are moves equal
bool operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return pm1.mFrom == pm2.mFrom
      && pm1.mDestination == pm2.mDestination
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
     << pm.mDestination << ", "
     << pm.mCapture << ")";
  return os;
}

} // namespace zoor
