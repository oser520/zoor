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

std::string pieceToStringLong(const PieceCode &piece) noexcept
{
  switch (piece) {
  case PieceCode::NONE:
    return "NONE";
  case PieceCode::PAWN:
    return "PAWN";
  case PieceCode::KNIGHT:
    return "KNIGHT";
  case PieceCode::BISHOP:
    return "BISHOP";
  case PieceCode::ROOK:
    return "ROOK";
  case PieceCode::QUEEN:
    return "QUEEN";
  case PieceCode::KING:
    return "KING";
  default:
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceCode value" << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::string colorToString(const PieceColor &color) noexcept {
  switch (color) {
  case PieceColor::NONE:
    return "N";
  case PieceColor::WHITE:
    return "W";
  case PieceColor::BLACK:
    return "B";
  default:
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceColor value" << std::endl;
    exit(EXIT_FAILURE);
  }

std::string colorToStringLong(const PieceColor &color) noexcept {
  switch (color) {
  case PieceColor::NONE:
    return "NONE";
  case PieceColor::WHITE:
    return "WHITE";
  case PieceColor::BLACK:
    return "BLACK";
  default:
    // TODO: throw some kind of exception and make error message more informative by
    // including function name, source file and line number
    std::cerr << "Unknown PieceColor value" << std::endl;
    exit(EXIT_FAILURE);
  }
}

} // namespace zoor
