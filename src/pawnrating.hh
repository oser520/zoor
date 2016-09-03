////////////////////////////////////////////////////////////////////////////////
//! @file pawnrating.hh
//! @author Omar A Serrano
//! @date 2016-09-03
////////////////////////////////////////////////////////////////////////////////
#ifndef _PAWNRATING_H
#define _PAWNRATING_H

//
// STL
//
#include <cstdint>

//
// zoor
//
#include "ipiecerating.hh"

namespace zoor {

//! @brief Represents the overall rating of a pawn given a current position on
//! a board.
class PawnRating
  : public IPieceRating
{
  bool mIsInCenter{false};
  bool mIsPassed{false};
  bool mCanPromote{false};
  // Indicates if there are no other pawns in ajoining columns.
  bool mIsIsolated{false};
  // Number of pawns it is blocking on this column.
  uint8_t mBlocking{0};

public:
  //! @copydoc PieceRating::compute(dim_t, tim_t, BasicBoard)
  PieceRating&
  compute(dim_t row, dim_t col, const BasicBoard &board) noexcept override;

  //! @copydoc PieceRating::rating()
  unsigned
  rating() noexcept override;
};

} // namespace zoor
#endif // _PAWNRATING_H
