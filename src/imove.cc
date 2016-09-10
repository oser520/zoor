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
#include "board.hh"

namespace zoor {

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

} // namespace zoor
