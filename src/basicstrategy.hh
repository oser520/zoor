////////////////////////////////////////////////////////////////////////////////
//! @file basicstrategy.hh
//! @author Omar A Serrano
//! @date 2016-06-29
////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICSTRATEGY_H
#define _BASICSTRATEGY_H

//
// zoor
//
#include "strategy.hh"

namespace zoor {

// Forward declaration.
class Board;

//! @brief A basic strategy for evaluating chess positions.
class BasicStrategy
  : public Strategy
{
  //! @param board The board to evaluate.
  //! @return The score for the player making a move. A positive, zero, or
  //! negative score reflects a winning, tied, or losing position,
  //! respectively.
  int
  score(const Board& board) noexcept override;
};

} // namespace zoor
#endif // _BASICSTRATEGY_H 
