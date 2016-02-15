/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

#include <cstdint>
#include <iostream>

namespace zoor {

using piececode_t = uint8_t;

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
  WHITE = 1 << 3,
  BLACK = 1 << 4
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

using piecevalue_t = short;

/**
 * Represents the value of a piece.
 */
enum class PieceValue: piecevalue_t
{
  NONE,
  PAWN,
  KNIGHT = 3,
  BISHOP = KNIGHT,
  ROOK = 5,
  QUEEN = 9,
  KING = 0x7fff
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
 * @brief Determine if the code represents a pawn.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a pawn.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isPawn(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a pawn.
 * @param piece The @c PieceCode.
 * @return True if piece is a pawn.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isPawn(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a knight.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a knight.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isKnight(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a knight.
 * @param piece The @c PieceCode.
 * @return True if piece is a knight.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isKnight(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a bishop.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a bishop.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isBishop(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a bishop.
 * @param piece The @c PieceCode.
 * @return True if piece is a bishop.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isBishop(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a rook.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a rook.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isRook(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a rook.
 * @param piece The @c PieceCode.
 * @return True if piece is a rook.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isRook(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a queen.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a queen.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isQueen(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a queen.
 * @param piece The @c PieceCode.
 * @return True if piece is a queen.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isQueen(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a king.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a king.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isKing(piececode_t code) noexcept;

/**
 * @brief Determine if piece is a king.
 * @param piece The @c PieceCode.
 * @return True if piece is a king.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isKing(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a piece with white color.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a white piece.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isWhite(piececode_t code) noexcept;

/**
 * @brief Determine if the color is white.
 * @param color The @c PieceColor.
 * @return True if the color is white.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isWhite(PieceColor color) noexcept;

/**
 * @brief Determine if the code represents a piece with black color.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents a black piece.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isBlack(piececode_t code) noexcept;

/**
 * @brief Determine if the color is black.
 * @param color The @c PieceColor.
 * @return True if the color is black.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isBlack(PieceColor color) noexcept;

/**
 * @brief Determine if the code represents a <em>PieceCode::NONE</em>.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents <em>PieceCode::NONE</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isPieceNone(piececode_t code) noexcept;

/**
 * @brief Determine if the piece is <em>PieceCode::NONE</em>.
 * @param piece The @c PieceCode.
 * @return True if piece is <em>PieceCode::NONE</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isPieceNone(PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents a <em>PieceColor::NONE</em>.
 * @param code The bit pattern reprsenting a piece and its color.
 * @return True if the code represents <em>PieceColor::NONE</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isColorNone(piececode_t code) noexcept;

/**
 * @brief Determine if the color is <em>PieceColor::NONE</em>.
 * @param color The @c PieceColor.
 * @return True if piece is <em>PieceColor::NONE</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isColorNone(PieceColor color) noexcept;

/**
 * @brief Determine if the code represents the same <em>piece</em>.
 * @param code The bit pattern reprsenting a piece and its color.
 * @param piece The @c PieceCode.
 * @return True if the code represents the <em>piece</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isSamePiece(piececode_t code, PieceCode piece) noexcept;

/**
 * @brief Determine if the code represents the same <em>color</em>.
 * @param code The bit pattern reprsenting a piece and its color.
 * @param color The @c PieceColor.
 * @return True if the code represents the <em>color</em>.
 * @throw Never throws.
 * TODO: make definition inline
 */
bool isSameColor(piececode_t code, PieceColor color) noexcept;

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
piececode_t operator|(const PieceColor &color, const PieceCode &piece) noexcept;

/**
 * @brief Logical negation operator for @c PieceColor.
 * @param color The @c PieceColor.
 * @return White if it is black, black if it is white, or none.
 * @throw Never throws.
 */
PieceColor operator~(const PieceColor &color) noexcept;

} // namespace zoor

#endif 
