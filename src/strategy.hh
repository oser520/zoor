////////////////////////////////////////////////////////////////////////////////
//! @file strategy.hh
//! @author Omar A Serrano
//! @date 2016-08-20
////////////////////////////////////////////////////////////////////////////////
#ifndef _STRATEGY_H
#define _STRATEGY_H

#include "istrategy.hh"
#include "piececount.hh"

namespace zoor {

class Board;

//! The default strategy for evaluating a chess position.
class Strategy
  : public IStrategy
{
  PieceCount mPieceCount;

public:
  //! @copydoc IStrategy::score()
  int
  score(const Board& board) noexcept;
};

} // namespace zoor
#endif // _STRATEGY_H
