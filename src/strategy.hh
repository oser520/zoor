////////////////////////////////////////////////////////////////////////////////
//! @file strategy.hh
//! @author Omar A Serrano
//! @date 2016-06-28
////////////////////////////////////////////////////////////////////////////////
#ifndef _ISTRATEGY_H
#define _ISTRATEGY_H


namespace zoor {

// Forward declaration.
class Board;

//! @brief An abstract strategy for evaluating a chess position.
struct IStrategy
{
  virtual
  ~IStrategy() noexcept = default;

  //! @param board The board to evaluate.
  //! @return The score for the player making a move. A positive, zero, or
  //! negative score reflects a winning, tied, or losing position,
  //! respectively.
  virtual int
  score(const Board& board) noexcept = 0;
};

} // namespace zoor
#endif // _ISTRATEGY_H
