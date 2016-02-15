/**
 * @file piececode.cc
 * @author Omar A Serrano
 * @date 2016-01-01
 */

#include <cstdlib>

#include "piececode.hh"

namespace zoor {

// get the piece value
PieceCode getPieceCode(piececode_t code) noexcept
{
  code &= static_cast<piececode_t>(PieceMask::PIECE);
  return static_cast<PieceCode>(code);
}

// get the color value
PieceColor getPieceColor(piececode_t code) noexcept
{
  code &= static_cast<piececode_t>(PieceMask::COLOR);
  return static_cast<PieceColor>(code);
}

// determine if code contains pawn
bool isPawn(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::PAWN;
}

// determine if code contains knight
bool isKnight(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::KNIGHT;
}

// determine if code contains bishop
bool isBishop(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::BISHOP;
}

// determine if code contains rook
bool isRook(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::ROOK;
}

// output operator for pieces
std::ostream& operator<<(std::ostream &os, const PieceCode &piece)
{
  switch (piece) {
  case PieceCode::NONE:
    os << "NONE";
    break;
  case PieceCode::PAWN:
    os << "PAWN";
    break;
  case PieceCode::KNIGHT:
    os << "KNIGHT";
    break;
  case PieceCode::BISHOP:
    os << "BISHOP";
    break;
  case PieceCode::ROOK:
    os << "ROOK";
    break;
  case PieceCode::QUEEN:
    os << "QUEEN";
    break;
  case PieceCode::KING:
    os << "KING";
    break;
  default:
    std::cerr << "Unknown PieceCode value" << std::endl;
    exit(EXIT_FAILURE);
  }

  return os;
}

// output operator for color
std::ostream& operator<<(std::ostream &os, const PieceColor &color)
{
  switch (color) {
  case PieceColor::NONE:
    os << "NONE";
    break;
  case PieceColor::WHITE:
    os << "WHITE";
    break;
  case PieceColor::BLACK:
    os << "BLACK";
    break;
  default:
    std::cerr << "Unknown PieceColor value" << std::endl;
    exit(EXIT_FAILURE);
  }

  return os;
}

// output operator for piece mask
std::ostream& operator<<(std::ostream &os, const PieceMask &mask)
{
  os << std::hex << std::showbase
     << static_cast<int>(mask)
     << std::dec << std::noshowbase;
  return os;
}

// logical or operator for color and piece to get bit pattern
piececode_t operator|(const PieceColor &color, const PieceCode &piece) noexcept
{
  return static_cast<piececode_t>(color) | static_cast<piececode_t>(piece);
}

// logical not operator for color
PieceColor operator~(const PieceColor &color) noexcept
{
  if (color == PieceColor::WHITE)
    return PieceColor::BLACK;
  else if (color == PieceColor::BLACK)
    return PieceColor::WHITE;
  else
    return color;
}

} // namespace zoor
