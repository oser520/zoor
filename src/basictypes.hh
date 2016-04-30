/////////////////////////////////////////////////////////////////////////////////////
/// @file basictypes.hh
/// @author Omar A Serrano
/// @date 2016-04-30
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICTYPES_H
#define _BASICTYPES_H

//
// STL
//
#include <cstdint>
#include <ostream>

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

//
// @brief Represents a chess piece and its color
//
using piece_t = uint8_t;

//
// @brief The type used for the dimension of a board.
//
using dim_t = int16_t;

///
/// @brief Represents a piece on the board.
/// @defails Since each piece on a board is represented in a byte, the type for each
/// Piece is an unsigned char.
/// @li NONE is no piece
/// @li P for pawn
/// @li N for knight
/// @li B for bishop
/// @li R for rook
/// @li Q for queen
/// @li K for king
///
enum class Piece: piece_t
{
  NONE, // 0b000
  P,    // 0b001
  N,    // 0b010
  B,    // 0b011
  R,    // 0b100
  Q,    // 0b101
  K     // 0b110
};

///
/// @brief Represents the color of a piece.
/// @details The @c Color can be logically ORed with a PiceCode to make a piece
/// have color.
/// @li NONE is no color
/// @li W for white
/// @li B for black
///
enum class Color: piece_t
{
  NONE,       // 0b00000
  W = 1 << 3, // 0b01000
  B = 1 << 4  // 0b10000
};

///
/// @brief A mask to get the @c Piece and @c Color from a bit pattern that
/// contains both.
///
enum class PieceMask: piece_t
{
  PIECE = 7, // 0b00111
  COLOR = 24 // 0b11000
};

///
/// @brief Get a @c Piece from a bit pattern.
/// @param piece The bit pattern containing a @c Piece.
/// @return A @c Piece.
/// @throw Never throws.
/// TODO: make definition inline after I've tested this function
///
Piece
piece(piece_t piece) noexcept;

///
/// @brief Get a @c Color from a bit pattern.
/// @param piece The bit pattern containing a @c Color.
/// @return A @c Color.
/// @throw Never throws.
/// TODO: make definition inline after I've tested this function
///
Color
color(piece_t piece) noexcept;

///
/// @brief Determine if the code represents a pawn.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a pawn.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isPawn(piece_t code) noexcept;

///
/// @brief Determine if piece is a pawn.
/// @param piece The @c Piece.
/// @return True if piece is a pawn.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isPawn(Piece piece) noexcept;

///
/// @brief Determine if the code represents a knight.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a knight.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isKnight(piece_t code) noexcept;

///
/// @brief Determine if piece is a knight.
/// @param piece The @c Piece.
/// @return True if piece is a knight.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isKnight(Piece piece) noexcept;

///
/// @brief Determine if the code represents a bishop.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a bishop.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isBishop(piece_t code) noexcept;

///
/// @brief Determine if piece is a bishop.
/// @param piece The @c Piece.
/// @return True if piece is a bishop.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isBishop(Piece piece) noexcept;

///
/// @brief Determine if the code represents a rook.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a rook.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isRook(piece_t code) noexcept;

///
/// @brief Determine if piece is a rook.
/// @param piece The @c Piece.
/// @return True if piece is a rook.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isRook(Piece piece) noexcept;

///
/// @brief Determine if the code represents a queen.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a queen.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isQueen(piece_t code) noexcept;

///
/// @brief Determine if piece is a queen.
/// @param piece The @c Piece.
/// @return True if piece is a queen.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isQueen(Piece piece) noexcept;

///
/// @brief Determine if the code represents a king.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a king.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isKing(piece_t code) noexcept;

///
/// @brief Determine if piece is a king.
/// @param piece The @c Piece.
/// @return True if piece is a king.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isKing(Piece piece) noexcept;

///
/// @brief Determine if the code represents a piece with white color.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a white piece.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isWhite(piece_t code) noexcept;

///
/// @brief Determine if the color is white.
/// @param color The @c Color.
/// @return True if the color is white.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isWhite(Color color) noexcept;

///
/// @brief Determine if the code represents a piece with black color.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents a black piece.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isBlack(piece_t code) noexcept;

///
/// @brief Determine if the color is black.
/// @param color The @c Color.
/// @return True if the color is black.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isBlack(Color color) noexcept;

///
/// @brief Determine if the code represents a <em>Piece::NONE</em>.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents <em>Piece::NONE</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isNotPiece(piece_t code) noexcept;

///
/// @brief Determine if the piece is <em>Piece::NONE</em>.
/// @param piece The @c Piece.
/// @return True if piece is <em>Piece::NONE</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isNotPiece(Piece piece) noexcept;

///
/// @brief Determine if the code represents a <em>Color::NONE</em>.
/// @param code The bit pattern reprsenting a piece and its color.
/// @return True if the code represents <em>Color::NONE</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isNotColor(piece_t code) noexcept;

///
/// @brief Determine if the color is <em>Color::NONE</em>.
/// @param color The @c Color.
/// @return True if piece is <em>Color::NONE</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isNotColor(Color color) noexcept;

///
/// @brief Determine if the code represents the same <em>piece</em>.
/// @param code The bit pattern reprsenting a piece and its color.
/// @param piece The @c Piece.
/// @return True if the code represents the <em>piece</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isSame(piece_t code, Piece piece) noexcept;

///
/// @brief Determine if the code represents the same <em>color</em>.
/// @param code The bit pattern reprsenting a piece and its color.
/// @param color The @c Color.
/// @return True if the code represents the <em>color</em>.
/// @throw Never throws.
/// TODO: make definition inline
///
bool
isSame(piece_t code, Color color) noexcept;

///
/// @brief Output operator for a @c Piece.
/// @details The @c Piece names are:
/// @li NONE
/// @li PAWN
/// @li KNIGHT
/// @li BISHOP
/// @li ROOK
/// @li QUEEN
/// @li KING
/// @param os The output stream.
/// @param piece The @c Piece.
/// @return A reference to the output stream.
///
std::ostream&
operator<<(std::ostream &os, const Piece &piece);

///
/// @brief Output operator for a @c Color.
/// @details The @c Color names are:
/// @li NONE
/// @li WHITE
/// @li BLACK
/// @param os The output stream.
/// @param color The @c Color.
/// @return A reference to the output stream.
///
std::ostream&
operator<<(std::ostream &os, const Color &color);

///
/// @brief Output operator for a @c PieceMask.
/// @details The @c PieceMask names are:
/// @li PIECE
/// @li COLOR
/// @param os The output stream.
/// @param mask The @c PieceMask.
/// @return A reference to the output stream.
///
std::ostream&
operator<<(std::ostream &os, const PieceMask &mask);

///
/// @brief Logical and operator for @c Color and @c Piece.
/// @param color The @c Color.
/// @param piece The @c Piece.
/// @return The bit pattern of ANDing the color and piece.
/// @throw Never throws.
///
piece_t
operator|(const Color &color, const Piece &piece) noexcept;

///
/// @brief Logical negation operator for @c Color.
/// @param color The @c Color.
/// @return White if it is black, black if it is white, or none.
/// @throw Never throws.
///
Color
operator~(const Color &color) noexcept;

///
/// @brief Obtain a short string code representing the piece.
/// @param code The bit code representing the piece and its color.
/// @return A short, 1 to 2 char, string code.
/// @throw Never throws.
///
const char*
shortString(piece_t code) noexcept;

} // namespace zoor
#endif // _BASICTYPES_H
