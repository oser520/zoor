////////////////////////////////////////////////////////////////////////////////
//! @file strategy.hh
//! @author Omar A Serrano
//! @date 2015-12-25
////////////////////////////////////////////////////////////////////////////////
#ifndef _STRATEGY_H
#define _STRATEGY_H

namespace zoor {

//! @brief An abstract strategy for evaluating a chess position.
struct Strategy
{
  virtual
  ~Strategy() noexcept = default;

  //! @return The score for the player making a move. A positive, zero, or
  //! negative score reflects a winning, tied, or losing position,
  //! respectively.
  virtual int
  score() noexcept = 0;
};

} // namespace zoor
#endif // _STRATEGY_H 
