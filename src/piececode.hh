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
  PAWN = 1,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING,
  WHITE = 1 << 5,
  BLACK = 1 << 6
};

} // namespace zoor

#endif 
