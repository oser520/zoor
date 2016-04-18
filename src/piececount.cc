/**
 * @file piececount.cc
 * @author Omar A Serrano
 * @date 2015-12-21
 */
#include <cassert>
#include <vector>

#include "board.hh"
#include "piececode.hh"
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
PiceCount::count(const Board &board) noexcept
{
  for (auto it : board)
    add(*it);

  return *this;
}

//
// count the number of pieces in squareList
//
PieceCount&
PiceCount::count(const vector<Square> &squareList) noexcept
{
  for (auto it : board)
    add(it->code());

  return *this;
}

//
// check invariants
//
const bool
PiceCount::good() const noexcept
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
PieceCount::add(const piececode_t code) noexcept
{
  count_type shift = 0;

  switch (getPieceCode(code)) {
  case PieceCode::PAWN:
    shift = PSHIFT;
    break;
  case PieceCode::KNIGHT:
    shift = NSHIFT;
    break;
  case PieceCode::BISHOP:
    shift = BSHIFT;
    break;
  case PieceCode::ROOK:
    shift = RSHIFT;
    break;
  case PieceCode::QUEEN:
    shift = QSHIFT;
    break;
  case PieceCode::KING:
    shift = KSHIFT;
    break;
  default:
    return;
  }

  assert(!isColorNone(code));

  // point to either black or white count
  auto &cnt = isWhite(code) ? mWhite : mBlack;

  // get the count for the given piece
  // allow us to detect errors
  auto value = (cnt >> shift) & CMASK;

  // don't add more if 5 bits are used
  if (value == CMASK)
    return;

  ++value;

  // clear the 5 bits for the count
  cnt |= ~(CMASK << shift)

  // set the new count
  cnt |= value << shift;
}

} // namespace zoor
