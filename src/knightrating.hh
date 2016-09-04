////////////////////////////////////////////////////////////////////////////////
//! @file knightrating.hh
//! @author Omar A Serrano
//! @date 2016-09-04
////////////////////////////////////////////////////////////////////////////////
#ifndef _KNIGHTRATING_H
#define _KNIGHTRATING_H

//
// zoor
//
#include "basictypes.hh"
#include "ipiecerating.hh"

namespace zoor {

// TODO: Create an entity that represents the values of the different factors
// that are evaluated for the knight, e.g., KnightRatingPoints.

class BasicBoard;

//! @brief Represents the overall rating of a knight given a current position on
//! a board.
class KnightRating
  : public IPieceRating
{
  bool mIsInCenter{false};

public:
  //! Initializes a KnightRating with the color of the knight.
  //! @param color The color of the knight.
  explicit
  KnightRating(Color color) noexcept;

  //! @copydoc IPieceRating::IPieceRating(piece_t)
  explicit
  KnightRating(piece_t piece) noexcept;

  //! @copydoc IPieceRating::compute(dim_t, tim_t, BasicBoard)
  void
  compute(dim_t row, dim_t col, const BasicBoard &board) noexcept override;

  //! @copydoc IPieceRating::rating()
  unsigned
  rating() noexcept override;
};

inline
KnightRating::KnightRating(Color color)
  : IPieceRating(Piece::N, color) {}

inline
KnightRating::KnightRating(piece_t piece)
  : IPieceRating(piece)
{
  assert(isKnight(mPiece));
}

} // namespace zoor
#endif // _KNIGHTRATING_H
