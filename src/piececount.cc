////////////////////////////////////////////////////////////////////////////////
//! @file piececount.cc
//! @author Omar A Serrano
//! @date 2015-12-21
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "piececount.hh"
#include "square.hh"

namespace zoor {

//
// using declarations
//
using std::vector;

//
// count the number of pieces in board
//
PieceCount&
PieceCount::count(const Board &board) noexcept
{
  // clear the count
  mWhite = 0;
  mBlack = 0;

  // count the pieces
  for (auto &it : board)
    add(it);

  return *this;
}

//
// count the number of pieces in squareList
//
PieceCount&
PieceCount::count(const vector<Square> &squareList) noexcept
{
  // clear the count
  mWhite = 0;
  mBlack = 0;

  // count the pieces
  for (auto& sq : squareList)
    add(sq.code());

  return *this;
}

//
// check invariants
//
bool
PieceCount::good() const noexcept
{
  return wKing() <= KMAX && bKing() <= KMAX
      && wQueen() <= QMAX && bQueen() <= QMAX
      && wRook() <= RMAX && bRook() <= RMAX
      && wBishop() <= BMAX && bBishop() <= BMAX
      && wKnight() <= NMAX && bKnight() <= NMAX
      && wPawn() <= PMAX && bPawn() <= PMAX;
}

//
// add the piece code to the white or black count
//
void
PieceCount::add(const piece_t code) noexcept
{
  count_type shift = 0;

  switch (getPiece(code)) {
  case Piece::P:
    shift = PSHIFT;
    break;
  case Piece::N:
    shift = NSHIFT;
    break;
  case Piece::B:
    shift = BSHIFT;
    break;
  case Piece::R:
    shift = RSHIFT;
    break;
  case Piece::Q:
    shift = QSHIFT;
    break;
  case Piece::K:
    shift = KSHIFT;
    break;
  default:
    return;
  }

  // point to either black or white count
  auto &cnt = isWhite(code) ? mWhite : mBlack;

  // get the count for the given piece
  auto value = (cnt >> shift) & CMASK;

  // don't add more if 5 bits are used to detect errors
  if (value == CMASK)
    return;

  ++value;

  // clear the 5 bits for the count
  cnt &= ~(CMASK << shift);

  // set the new count
  cnt |= value << shift;
}

} // namespace zoor
