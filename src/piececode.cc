/**
 * @file piececode.cc
 * @author Omar A Serrano
 * @date 2016-01-01
 */

#include <cstdlib>

#include "piececode.hh"

namespace zoor {

PieceCode getPieceCode(piececode_t code) noexcept
{
  code &= static_cast<piececode_t>(PieceMask::PIECE);
  return static_cast<PieceCode>(code);
}

PieceColor getPieceColor(piececode_t code) noexcept
{
  code &= static_cast<piececode_t>(PieceMask::COLOR);
  return static_cast<PieceColor>(code);
}

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
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceCode value" << std::endl;
    exit(EXIT_FAILURE);
  }

  return os;
}

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
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceColor value" << std::endl;
    exit(EXIT_FAILURE);
  }

  return os;
}

std::ostream& operator<<(std::ostream &os, const PieceMask &mask)
{
  os << std::hex << std::showbase
     << static_cast<piececode_t>(mask)
     << std::dec << std::noshowbase;
  return os;
}

piececode_t operator&(const PieceColor color, const PieceCode piece) noexcept
{
  return static_cast<piececode_t>(color) & static_cast<piececode_t>(piece);
}

} // namespace zoor
