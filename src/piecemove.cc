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

PieceMove::PieceMove
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mFrom(row, column, piece, color) {}

PieceMove::PieceMove(dim_type row, dim_type column, piececode_t code) noexcept
  : mFrom(row, column, code) {}

PieceMove::PieceMove
  (dim_type fromRow,
   dim_type fromColumn,
   piececode_t code,
   dim_type toRow,
   dim_type toColumn) noexcept
  : mFrom(fromRow, fromColumn, code),
    mPromotion(toRow, toColumn) {}

dim_type PieceMove::fromRow() const noexcept
{
  return mFrom.row();
}

dim_type PieceMove::fromColumn() const noexcept
{
  return mFrom.column();
}

dim_type PieceMove::toRow() const noexcept
{
  return mDestination.row();
}

dim_type PieceMove::toColumn() const noexcept
{
  return mDestination.column();
}

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

PieceMove& PieceMove::setPiece
  (dim_type row,
   dim_type column,
   piececode_t code) noexcept
{
  mFrom.setRow(row)
       .setColumn(column)
       .setPieceCode(piece);
  return *this;
}

Square PieceMove::fromSquare() const noexcept
{
  return mFrom;
}

Square PieceMove::piece() const noexcept
{
  return mFrom.piece();
}

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

PieceMove& PieceMove::setCapture
  (dim_type row,
   dim_type column,
   piececode_t code) noexcept
{
  mCapture.setRow(row)
          .setColumn(column)
          .setPieceCode(piece);
  return *this;
}

bool PieceMove::isCapture() const noexcept
{
  return mCapture.piece() != PieceCode::NONE;
}

Square PieceMove::capture() const noexcept
{
  return mCapture;
}

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

PieceMove&
PieceMove::setPromotion(PieceCode piece, PieceColor color) noexcept
{
  mPromotion.setPiece(piece).setColor(color);
  return *this;
}

PieceMove& PieceMove::setPromotion(piececode_t code) noexcept
{
  mPromotion.setPieceCode(code);
  return *this;
}

bool PieceMove::isPromotion() const noexcept
{
  return mPromotion.piece() != PieceCode::NONE;
}

Square PieceMove::promotion() const noexcept
{
  return mPromotion;
}

PieceMove& PieceMove::setToRow(dim_type row) noexcept
{
  mPromotion.setRow(row);
  return *this;
}

PieceMove& PieceMove::setToColumn(dim_type column) noexcept
{
  mPromotion.setColumn(column);
  return *this;
}

PieceMove& PieceMove::setDestination(dim_type row, dim_type column) noexcept
{
  mPromotion.setRow(row).setColumn(column);
  return *this;
}

bool operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return pm1.mFrom == pm2.mFrom
      && pm1.mDestination == pm2.mDestination
      && pm1.mCapture == pm2.mCapture;
}

bool operator!=(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return !(pm1 == pm2);
}

std::ostream& operator<<(std::ostream &os, const PieceMove &pm)
{
  os << "("
     << pm.mFrom << ", "
     << pm.mDestination << ", "
     << pm.mCapture << ")";
  return os;
}

} // namespace zoor
