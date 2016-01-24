/**
 * @file piecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-04
 */

#include <iostream>
#include <utility>
#include <cassert>

#include "piecemoves.hh"
#include "piececode.hh"
#include "square.hh"

namespace zoor {

/**
 * TODO: implement thread safety
 * TODO: throw exceptions
 * TODO: implement operator[]
 */

using dim_type = PieceMoves::dim_type;
using iterator = PieceMoves::iterator;
using const_iterator = PieceMoves::const_iterator;
using size_type = PieceMoves::size_type;

// PieceMove

PieceMove::PieceMove
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mFrom(row, column, piece, color) {}

PieceMove::PieceMove(dim_type row, dim_type column, piececode_t code) noexcept
  : mFrom(row, column, code) {}

dim_type PieceMove::rowFrom() const noexcept
{
  return mFrom.row();
}

dim_type PieceMove::columnFrom() const noexcept
{
  return mFrom.column();
}

dim_type PieceMove::rowTo() const noexcept
{
  return mDestination.row();
}

dim_type PieceMove::columnTo() const noexcept
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

Square PieceMove::piece() const noexcept
{
  return mFrom;
}

// PieceMoves

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
  assert(piece != PieceCode::NONE);

  if (mSquare.piece() != piece) {
    mSquare.setPiece(piece);
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setColor(PieceColor color) noexcept
{
  assert(color != PieceColor::NONE);

  if (mSquare.color() != color) {
    mSquare.setColor(color);
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setRow(dim_type row) noexcept
{
  if (mSquare.row() != row) {
    mSquare.setRow(row);
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setColumn(dim_type column) noexcept
{
  if (mSquare.column() != column) {
    mSquare.setColumn(column);
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setSquare(const Square &square) noexcept
{
  assert(square.piece() != PieceCode::NONE);
  assert(square.color() != PieceColor::NONE);

  if (mSquare != square) {
    mSquare = square;
    if (!empty()) clear();
  }
  return *this;
}

PieceMoves& PieceMoves::setSquare(Square &&square) noexcept
{
  assert(square.piece() != PieceCode::NONE);
  assert(square.color() != PieceColor::NONE);

  if (mSquare != square) {
    mSquare = std::move(square);
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

Square PieceMoves::square() const noexcept
{
  return mSquare;
}

bool PieceMoves::empty() const noexcept
{
  return mMoves.empty();
}

size_type PieceMoves::size() const noexcept
{
  return mMoves.size();
}

iterator PieceMoves::begin() noexcept
{
  return mMoves.begin();
}

iterator PieceMoves::end() noexcept
{
  return mMoves.end();
}

const_iterator PieceMoves::cbegin() noexcept
{
  return mMoves.cbegin();
}

const_iterator PieceMoves::cend() noexcept
{
  return mMoves.cend();
}

const_iterator PieceMoves::begin() const noexcept
{
  return mMoves.cbegin();
}

const_iterator PieceMoves::end() const noexcept
{
  return mMoves.cend();
}

PieceMoves& PieceMoves::push_back(const Square &square)
{
  // TODO: check if moves is legal
  mMoves.push_back(square);
  return *this;
}

PieceMoves& PieceMoves::push_back(Square &&square)
{
  // TODO: check if moves is legal
  mMoves.push_back(std::move(square));
  return *this;
}

PieceMoves& PieceMoves::pop_back() noexcept
{
  if (!empty())
    mMoves.pop_back();
  return *this;
}

Square PieceMoves::back() const
{
  // TODO: throw exception if mMoves is empty
  return mMoves.back();
}

Square PieceMoves::front() const
{
  // TODO: throw exception if mMoves is empty
  return mMoves.front();
}

PieceMoves& PieceMoves::clear()
{
  mMoves.clear();
  return *this;
}

std::ostream& operator<<(std::ostream &os, const PieceMoves &pm)
{
  os << "(" << pm.mSquare << ", (";
  auto loops = pm.size();
  if (loops) {
    for (size_t i = 0; i < loops - 1; ++i)
      os << pm.mMoves[i] << ", ";
    os << pm.mMoves[loops-1];
  }
  os << "))";
  return os;
}

bool operator==(const PieceMoves &pm1, const PieceMoves &pm2) noexcept
{
  return pm1.mSquare == pm2.mSquare && pm1.mMoves == pm2.mMoves;
}

bool operator!=(const PieceMoves &pm1, const PieceMoves &pm2) noexcept
{
  return !(pm1 == pm2);
}

} // namespace zoor
