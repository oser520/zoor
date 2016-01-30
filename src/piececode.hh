/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

#include <iostream>

namespace zoor {

using piececode_t = unsigned char;

/**
 * Represents a piece on the board.
 *
 * Since each piece on a board is represented in a byte, the type for
 * each PieceCode is an unsigned char.
 */
enum class PieceCode: piececode_t
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
enum class PieceColor: piececode_t
{
  NONE,
  WHITE = 1 << 4,
  BLACK = 1 << 5
};

/**
 * A mask to get the @c PieceCode and @c PieceColor from a bit pattern that contains
 * both.
 */
enum class PieceMask: piececode_t
{
  PIECE = static_cast<piececode_t>(7), // 0b00111
  COLOR = static_cast<piececode_t>(24) // 0b11000
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
 * @brief Get a @c PieceCode from a bit pattern.
 * @param code The bit pattern containing a @c PieceCode.
 * @return A @c PieceCode.
 * @throw Never throws.
 * TODO: make definition inline after I've tested this function
 */
PieceCode getPieceCode(piececode_t code) noexcept;

/**
 * @brief Get a @c PieceColor from a bit pattern.
 * @param code The bit pattern containing a @c PieceColor.
 * @return A @c PieceColor.
 * @throw Never throws.
 * TODO: make definition inline after I've tested this function
 */
PieceColor getPieceColor(piececode_t code) noexcept;

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

/**
 * Output operator for a @c PieceMask.
 *
 * The @c PieceMask names are:
 * @li PIECE
 * @li COLOR
 *
 * @param os The output stream.
 * @param mask The @c PieceMask.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceMask &mask);

/**
 * @brief Logical and operator for @c PieceColor and @c PieceCode.
 * @param color The @c PieceColor.
 * @param piece The @c PieceCode.
 * @return The bit pattern of ANDing the color and piece.
 * @throw Never throws.
 */
piececode_t operator&(const PieceColor color, const PieceCode piece) noexcept;

} // namespace zoor

#endif 
