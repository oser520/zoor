/**
 * @file piececode.cc
 * @author Omar A Serrano
 * @date 2016-01-01
 */

#include <string>
#include <cstdlib>

#include "piececode.hh"

namespace zoor {

std::string pieceToString(const PieceCode &piece) noexcept
{
  switch (piece) {
  case PieceCode::NONE:
    return "N";
  case PieceCode::PAWN:
    return "P";
  case PieceCode::KNIGHT:
    return "KN";
  case PieceCode::BISHOP:
    return "B";
  case PieceCode::ROOK:
    return "R";
  case PieceCode::QUEEN:
    return "Q";
  case PieceCode::KING:
    return "KI";
  default:
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceCode value" << std::endl;
    exit(EXIT_FAILURE);
  }
}

} // namespace zoor
