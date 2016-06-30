////////////////////////////////////////////////////////////////////////////////
//! @file strategy.hh
//! @author Omar A Serrano
//! @date 2015-12-25
////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICSTRATEGY_H
#define _BASICSTRATEGY_H

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
