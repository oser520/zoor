////////////////////////////////////////////////////////////////////////////////
//! @file ipiecerating.hh
//! @author Omar A Serrano
//! @date 2016-09-01
////////////////////////////////////////////////////////////////////////////////
#ifndef _IPIECERATING_H
#define _IPIECERATING_H

#include <cstdint>
#include "basictypes.hh"

namespace zoor {

//! @brief Represents the overall rating of a piece, taking into account its
//! mobility, the number of pieces it is currently attacking, and the number of
//! pieces attacking it.
class IPieceRating
{
  Piece mPiece;
  uint8_t mMobility{0};
  uint8_t mAttack{0};
  uint8_t mThreat{0};

public:
  //! Dtor.
  virtual
  ~IPieceRating() noexcept = default;

  //! @return The type of Piece represented.
  Piece
  type() const noexcept;

  //! @return The mobility of the chess piece.
  unsigned
  mobility() const noexcept;

  //! @return The number of pieces it attacks.
  unsigned
  attack() const noexcept;

  //! @return The number of pieces attacking it.
  unsigned
  threat() const noexcept;

  //! @brief Computes the overall value of the piece at the given row and
  //! column.
  //! @param row The row of the square where piece is located.
  //! @param col The column of the square where piece is located.
  //! @return This PieceRating.
  virtual PieceRating&
  compute(dim_t row, dim_t col, const BasicBoard &board) noexcept = 0;

  //! @return The overall rating of the piece, excluding its nominal value.
  virtual unsigned
  rating() noexcept = 0;
};

//! @return The type of Piece represented.
inline Piece
PieceRating::type() const noexcept
{
  return mPiece;
}

//! @return The mobility of the chess piece.
inline unsigned
PieceRating::mobility() const noexcept
{
  return mMobility;
}

//! @return The number of pieces it attacks.
inline unsigned
PieceRating::attack() const noexcept
{
  return mAttack;
}

//! @return The number of pieces attacking it.
inline unsigned
PieceRating::threat() const noexcept
{
  return mThreat;
}

} // namespace zoor
#endif // _IPIECERATING_H
