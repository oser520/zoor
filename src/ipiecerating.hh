////////////////////////////////////////////////////////////////////////////////
//! @file ipiecerating.hh
//! @author Omar A Serrano
//! @date 2016-09-01
////////////////////////////////////////////////////////////////////////////////
#ifndef _IPIECERATING_H
#define _IPIECERATING_H

//
// STL
//
#include <cassert>
#include <cstdint>

//
// zoor
//
#include "basictypes.hh"

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

namespace zoor {

//! @brief Represents the overall rating of a piece, taking into account its
//! mobility, the number of pieces it is currently attacking, and the number of
//! pieces attacking it.
class IPieceRating
{
  Piece mPiece;
  Color mColor;
  uint8_t mMobility{0};
  uint8_t mAttack{0};
  uint8_t mThreat{0};

public:
  //! Initializes piece rating with a piece.
  //! @param piece The type of piece.
  //! @param color The color of the piece.
  IPieceRating(Piece piece, Color color) noexcept;

  //! Initializes piece rating with a piece.
  //! @param piece The bit code representing the piece.
  IPieceRating(piece_t piece) noexcept;

  //! Defaul ctor.
  IPieceRating() noexcept = default;

  //! Dtor.
  virtual
  ~IPieceRating() noexcept = default;

  //! @return The type of Piece represented.
  Piece
  type() const noexcept;

  //! @return The color of the piece.
  Color
  color() const noexcept;

  //! @return The bit code of the piece.
  piece_t
  code() const noexcept;

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
  virtual void
  compute(dim_t row, dim_t col, const BasicBoard &board) noexcept = 0;

  //! @return The overall rating of the piece, excluding its nominal value.
  virtual unsigned
  rating() noexcept = 0;
};

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

inline
IPieceRating(Piece piece, Color color) noexcept
  : mPiece(piece), mColor(color)
{
  assert(isPiece(piece));
  assert(isColor(color));
}

inline
IPieceRating(piece_t piece) noexcept
  : IPieceRating(getPiece(piece), getColor(color)) {}

inline Piece
PieceRating::type() const noexcept
{
  return mPiece;
}

inline Color
PieceRating::color() const noexcept
{
  return mColor;
}

inline piece_t
PieceRating::code() const noexcept
{
  return mColor | mPiece;
}

inline unsigned
PieceRating::mobility() const noexcept
{
  return mMobility;
}

inline unsigned
PieceRating::attack() const noexcept
{
  return mAttack;
}

inline unsigned
PieceRating::threat() const noexcept
{
  return mThreat;
}

} // namespace zoor
#endif // _IPIECERATING_H
