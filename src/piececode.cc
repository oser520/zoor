/**
 * @file piececode.cc
 * @author Omar A Serrano
 * @date 2016-01-01
 */

#include <string>
#include <cstdlib>

#include "piececode.hh"

namespace zoor {

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

std::string pieceToString(const PieceCode &piece)
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

std::string pieceToStringLong(const PieceCode &piece)
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

std::string colorToString(const PieceColor &color)
{
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

std::string colorToStringLong(const PieceColor &color)
{
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
