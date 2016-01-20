/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

#include <iostream>

namespace zoor {

/**
 * Represents a piece on the board.
 *
 * Since each piece on a board is represented in a byte, the type for
 * each PieceCode is an unsigned char.
 */
enum class PieceCode: unsigned char
{
  NONE = 0,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
};

/**
 * Represents the color of a piece. 
 *
 * The PieceColor can be logically ORed with a PiceCode to
 * make a piece have color.
 */
enum class PieceColor: unsigned char
{
  NONE,
  WHITE = 1 << 4,
  BLACK = 1 << 5
};

/**
 * A mask to get the @c PieceCode and @c PieceColor from a bit pattern that contains
 * both.
 */
enum class PieceMask: unsigned char
{
  PIECE = static_cast<unsigned char>(7), // 0b00111
  COLOR = static_cast<unsigned char>(24) // 0b11000
};

/**
 * Represents the value of a piece.
 */
enum class PieceValue: unsigned short
{
  NONE,
  PAWN,
  KNIGHT = 3,
  BISHOP = KNIGHT,
  ROOK = 5,
  QUEEN = 9,
  KING = 0xffff
};

/**
 * Output operator for a @c PieceCode.
 *
 * The @c PieceCode names are:
 * @li NONE
 * @li PAWN
 * @li KNIGHT
 * @li BISHOP
 * @li ROOK
 * @li QUEEN
 * @li KING
 *
 * @param os The output stream.
 * @param piece The @c PieceCode.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceCode &piece);

/**
 * Output operator for a @c PieceColor.
 *
 * The @c PieceColor names are:
 * @li NONE
 * @li WHITE
 * @li BLACK
 *
 * @param os The output stream.
 * @param color The @c PieceColor.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceColor &color);

} // namespace zoor

#endif 
