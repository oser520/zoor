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
#include "basictypes.hh"
#include "ipiecerating.hh"

namespace zoor {

class BasicBoard;

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
  //! Initializes a PawnRating with the color of the pawn.
  //! @param color The color of the pawn.
  explicit
  PawnRating(Color color) noexcept;

  //! @copydoc PieceRating::PieceRating(piece_t)
  explicit
  PawnRating(piece_t piece) noexcept;

  //! @copydoc PieceRating::compute(dim_t, tim_t, BasicBoard)
  void
  compute(dim_t row, dim_t col, const BasicBoard &board) noexcept override;

  //! @copydoc PieceRating::rating()
  unsigned
  rating() noexcept override;
};

inline
PawnRating::PawnRating(Color color)
  : IPieceRating(Piece::P, color) {}

inline
PawnRating::PawnRating(piece_t piece)
  : IPieceRating(piece) {}

} // namespace zoor
#endif // _PAWNRATING_H
