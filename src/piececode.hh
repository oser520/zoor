/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

namespace zoor {

/**
 * Represents the piece or color of a piece.
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

enum class PieceColor: unsigned char
{
  WHITE = 1 << 4,
  BLACK = 1 << 5
};

/**
 * Represents the value of a piece.
 */
enum class PieceValue: unsigned short
{
  PAWN = 1,
  KNIGHT = 3,
  BISHOP = KNIGHT,
  ROOK = 5,
  QUEEN = 9,
  KING = ~0
};

} // namespace zoor

#endif 
