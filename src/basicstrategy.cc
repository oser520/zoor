////////////////////////////////////////////////////////////////////////////////
//! @file basicstrategy.cc
//! @author Omar A Serrano
//! @date 2016-06-29
////////////////////////////////////////////////////////////////////////////////

//
// zoor
//
#include "basicstrategy.hh"
#include "board.hh"

namespace zoor {

int
BasicStrategy::score(const Board &board) noexcept
{
  // Factors to be evaluated
  // 1. number of pieces for each color
  // 2. how well are pieces positioned
  //   - is king castled
  //   - is king well protected
  //   - are knights out of the first rank
  //   - are bishops out of the first rank
  //   - are rooks connected
  //   - are rooks in open column
  //   - range of mobility of pieces, e.g., how many moves can a bishop make
  //   - how many enemy pieces are being attacked
  //   - how many pieces are in attacking position
  //   - how many pieces are in danger
  //   - is king in check
  //   - are pawns connected
  //   - are pawns advanced
  //   - any doubled pawns
  return 0;
}

} // namespace zoor
