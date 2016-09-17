////////////////////////////////////////////////////////////////////////////////
//! @file imove.cc
//! @author Omar A Serrano
//! @date 2016-09-09
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>

//
// zoor
//
#include "basictypes.hh"
#include "imove.hh"

namespace zoor {

class Board;

IMove::IMove(dim_t row, dim_t col, const Board &board)
  : mRow(row),
    mCol(col),
    mBoard(board),
    mColor(mBoard(mRow, mCol).color())
{
  // TODO: return exception instead of asserting
  assert(isColor(mColor));
  assert(mColor == mBoard.nextTurn());
}

void
IMove::square(dim_t row, dim_t col)
{
  // TODO: return exception instead of asserting
  assert(mBoard(row, col).piece() == type());
  assert(mBoard(row, col).color() == color());
  mRow = row;
  mCol = col;
}

} // namespace zoor
