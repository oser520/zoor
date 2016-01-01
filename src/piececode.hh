/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

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

/**
 * Gets the initial letter for the name of a given piece.
 *
 * The intial letter of the pieces are N, P, K, B, R, Q, and K. The letters
 * correspond to @c PieceCode values for none, pawn, knight, bishop, root,
 * queen, and king.
 *
 * @param piece The @c PieceCode.
 * @return A string representing the one letter intial of the piece.
 */
string pieceString(const PieceCode &piece) noexcept;
string longPieceString(const PieceCode &piece) noexcept;
string colorString(const PieceColor &color) noexcept;
string longColorString(const PieceColor &color) noexcept;

} // namespace zoor

#endif 
