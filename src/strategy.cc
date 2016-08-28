////////////////////////////////////////////////////////////////////////////////
//! @file strategy.cc
//! @author Omar A Serrano
//! @date 2016-08-27
////////////////////////////////////////////////////////////////////////////////

//
// zoor
//
#include "strategy.hh"
#include "board.hh"

namespace zoor {

int
Strategy::score(const Board& board) noexcept
{
  mPieceCount.count(board);
  // TODO: things to consider:
  // are knights developed? what is mobility?
  // are bishops developed? what is mobility?
  // are rooks developed? what is mobility?
  // are rooks connected?
  // is king castled?
  // is king attacked? is king protected? is king's vicinity attacked?
  // how many pieces are attacked?
  // who controls the board?
  return 0;
}

} // namespace zoor
