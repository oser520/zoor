/////////////////////////////////////////////////////////////////////////////////////
/// @file basictypes.cc
/// @author Omar A Serrano
/// @date 2016-04-30
/////////////////////////////////////////////////////////////////////////////////////

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

//
// output operator for pieces
//
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

//
// output operator for color
//
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

//
// output operator for piece mask
//
std::ostream&
operator<<(std::ostream &os, PieceMask mask)
{
  os << std::hex << std::showbase
     << static_cast<int>(mask)
     << std::dec << std::noshowbase;
  return os;
}

//
// logical not operator for color
//
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

//
// get a short string code representing a piece
//
const char*
shortString(piece_t piece) noexcept
{
  if (isWhite(piece)) {
    switch (getPiece(piece)) {
    case Piece::P:
      return "WP";
    case Piece::N:
      return "WKn";
    case Piece::B:
      return "WB";
    case Piece::R:
      return "WR";
    case Piece::Q:
      return "WQ";
    case Piece::K:
      return "WKi";
    case Piece::NONE:
      return "0";
    default:
      assert(false);
    }
  } else {
    switch (getPiece(piece)) {
    case Piece::P:
      return "BP";
    case Piece::N:
      return "BKn";
    case Piece::B:
      return "BB";
    case Piece::R:
      return "BR";
    case Piece::Q:
      return "BQ";
    case Piece::K:
      return "BKi";
    case Piece::N:
      return "0";
    default:
      assert(false);
    }
  }
}

} // namespace zoor
