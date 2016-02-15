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

// determine if code contains pawn
bool isPawn(PieceCode piece) noexcept
{
  return piece == PieceCode::PAWN;
}

// determine if code contains knight
bool isKnight(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::KNIGHT;
}

// determine if code contains knight
bool isKnight(PieceCode piece) noexcept
{
  return piece == PieceCode::KNIGHT;
}

// determine if code contains bishop
bool isBishop(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::BISHOP;
}

// check if the piece is a bishop
bool isBishop(PieceCode piece) noexcept
{
  return piece == PieceCode::BISHOP;
}

// determine if code contains rook
bool isRook(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::ROOK;
}

// check if the piece is a rook
bool isRook(PieceCode piece) noexcept
{
  return piece == PieceCode::ROOK;
}

// determine if code contains queen
bool isQueen(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::QUEEN;
}

// check if the piece is a queen
bool isQueen(PieceCode piece) noexcept
{
  return piece == PieceCode::QUEEN;
}

// determine if code contains king
bool isKing(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::KING;
}

// determine if code contains a white piece
bool isWhite(piececode_t code) noexcept
{
  return getPieceColor(code) == PieceColor::WHITE;
}

// determine if code contains a black piece
bool isBlack(piececode_t code) noexcept
{
  return getPieceColor(code) == PieceColor::BLACK;
}

// determine if code does not contain a piece
bool isPieceNone(piececode_t code) noexcept
{
  return getPieceCode(code) == PieceCode::NONE;
}

// determine if code does not contain a color
bool isColorNone(piececode_t code) noexcept
{
  return getPieceColor(code) == PieceColor::NONE;
}

// determine if bit code contains the piece
bool isSamePiece(piececode_t code, PieceCode piece) noexcept
{
  return getPieceCode(code) == piece;
}

// determine if bit code contains the color
bool isSameColor(piececode_t code, PieceColor color) noexcept
{
  return getPieceColor(code) == color;
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
