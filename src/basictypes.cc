////////////////////////////////////////////////////////////////////////////////
//! @file basictypes.cc
//! @author Omar A Serrano
//! @date 2016-04-30
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>
#include <cstdlib>
#include <ostream>

//
// zoor
//
#include "basictypes.hh"

namespace zoor {

//! @brief Output operator for a @c Piece.
//! @details The @c Piece names are:
//! @li NONE
//! @li PAWN
//! @li KNIGHT
//! @li BISHOP
//! @li ROOK
//! @li QUEEN
//! @li KING
//! @param os The output stream.
//! @param piece The @c Piece.
//! @return A reference to the output stream.
std::ostream&
operator<<(std::ostream &os, Piece piece)
{
  switch (piece) {
  case Piece::NONE:
    os << "NONE";
    break;
  case Piece::P:
    os << "PAWN";
    break;
  case Piece::N:
    os << "KNIGHT";
    break;
  case Piece::B:
    os << "BISHOP";
    break;
  case Piece::R:
    os << "ROOK";
    break;
  case Piece::Q:
    os << "QUEEN";
    break;
  case Piece::K:
    os << "KING";
    break;
  default:
    // should never get here
    assert(false);
  }

  return os;
}

//! @brief Output operator for a @c Color.
//! @details The @c Color names are:
//! @li NONE
//! @li WHITE
//! @li BLACK
//! @param os The output stream.
//! @param color The @c Color.
//! @return A reference to the output stream.
std::ostream&
operator<<(std::ostream &os, Color color)
{
  switch (color) {
  case Color::NONE:
    os << "NONE";
    break;
  case Color::W:
    os << "WHITE";
    break;
  case Color::B:
    os << "BLACK";
    break;
  default:
    // should never get here
    assert(false);
  }

  return os;
}

//! @brief Output operator for a @c PieceMask.
//! @details The @c PieceMask names are:
//! @li PIECE
//! @li COLOR
//! @param os The output stream.
//! @param mask The @c PieceMask.
//! @return A reference to the output stream.
std::ostream&
operator<<(std::ostream &os, PieceMask mask)
{
  os << std::hex << std::showbase
     << static_cast<int>(mask)
     << std::dec << std::noshowbase;
  return os;
}

//! @brief Logical negation operator for @c Color.
//! @param color The @c Color.
//! @return White if it is black, black if it is white, or none.
//! @throw Never throws.
Color
operator~(Color color) noexcept
{
  if (isWhite(color))
    return Color::B;
  else if (isBlack(color))
    return Color::W;
  else
    return color;
}

//! @brief Obtain a short string piece code representing the piece.
//! @param piece The bit code representing the piece and its color.
//! @return A short, 1 to 2 char, string code.
//! @throw Never throws.
const char*
shortString(piece_t piece) noexcept
{
  if (isWhite(piece)) {
    switch (getPiece(piece)) {
    case Piece::P:
      return "P";
    case Piece::N:
      return "N";
    case Piece::B:
      return "B";
    case Piece::R:
      return "R";
    case Piece::Q:
      return "Q";
    case Piece::K:
      return "K";
    case Piece::NONE:
      return "0";
    default:
      assert(false);
    }
  } else {
    switch (getPiece(piece)) {
    case Piece::P:
      return "p";
    case Piece::N:
      return "n";
    case Piece::B:
      return "b";
    case Piece::R:
      return "r";
    case Piece::Q:
      return "q";
    case Piece::K:
      return "k";
    case Piece::NONE:
      return "0";
    default:
      assert(false);
    }
  }
}

} // namespace zoor
