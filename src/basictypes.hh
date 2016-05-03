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
/// @details The @c Color can be logically ORed with a Pice to make a piece
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
///
Piece
getPiece(piece_t piece) noexcept;

///
/// @brief Get a @c Color from a bit pattern.
/// @param piece The bit pattern containing a @c Color.
/// @return A @c Color.
/// @throw Never throws.
///
Color
getColor(piece_t piece) noexcept;

///
/// @brief Determine if the piece code represents a pawn.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a pawn.
/// @throw Never throws.
///
bool
isPawn(piece_t piece) noexcept;

///
/// @brief Determine if piece is a pawn.
/// @param piece The @c Piece.
/// @return True if piece is a pawn.
/// @throw Never throws.
///
bool
isPawn(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a knight.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a knight.
/// @throw Never throws.
///
bool
isKnight(piece_t piece) noexcept;

///
/// @brief Determine if piece is a knight.
/// @param piece The @c Piece.
/// @return True if piece is a knight.
/// @throw Never throws.
///
bool
isKnight(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a bishop.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a bishop.
/// @throw Never throws.
///
bool
isBishop(piece_t piece) noexcept;

///
/// @brief Determine if piece is a bishop.
/// @param piece The @c Piece.
/// @return True if piece is a bishop.
/// @throw Never throws.
///
bool
isBishop(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a rook.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a rook.
/// @throw Never throws.
///
bool
isRook(piece_t piece) noexcept;

///
/// @brief Determine if piece is a rook.
/// @param piece The @c Piece.
/// @return True if piece is a rook.
/// @throw Never throws.
///
bool
isRook(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a queen.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a queen.
/// @throw Never throws.
///
bool
isQueen(piece_t piece) noexcept;

///
/// @brief Determine if piece is a queen.
/// @param piece The @c Piece.
/// @return True if piece is a queen.
/// @throw Never throws.
///
bool
isQueen(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a king.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a king.
/// @throw Never throws.
///
bool
isKing(piece_t piece) noexcept;

///
/// @brief Determine if piece is a king.
/// @param piece The @c Piece.
/// @return True if piece is a king.
/// @throw Never throws.
///
bool
isKing(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a piece with white color.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a white piece.
/// @throw Never throws.
///
bool
isWhite(piece_t piece) noexcept;

///
/// @brief Determine if the color is white.
/// @param color The @c Color.
/// @return True if the color is white.
/// @throw Never throws.
///
bool
isWhite(Color color) noexcept;

///
/// @brief Determine if the piece code represents a piece with black color.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents a black piece.
/// @throw Never throws.
///
bool
isBlack(piece_t piece) noexcept;

///
/// @brief Determine if the color is black.
/// @param color The @c Color.
/// @return True if the color is black.
/// @throw Never throws.
///
bool
isBlack(Color color) noexcept;

///
/// @brief Determine if the piece code represents a <em>Piece::NONE</em>.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents <em>Piece::NONE</em>.
/// @throw Never throws.
///
bool
notPiece(piece_t piece) noexcept;

///
/// @brief Determine if the piece is <em>Piece::NONE</em>.
/// @param piece The @c Piece.
/// @return True if piece is <em>Piece::NONE</em>.
/// @throw Never throws.
///
bool
notPiece(Piece piece) noexcept;

///
/// @brief Determine if the piece code represents a <em>Color::NONE</em>.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @return True if the piece code represents <em>Color::NONE</em>.
/// @throw Never throws.
///
bool
notColor(piece_t piece) noexcept;

///
/// @brief Determine if the color is <em>Color::NONE</em>.
/// @param color The @c Color.
/// @return True if piece is <em>Color::NONE</em>.
/// @throw Never throws.
///
bool
notColor(Color color) noexcept;

///
/// @brief Determine if the piece code represents the same <em>piece</em>.
/// @param code The bit pattern reprsenting a piece and its color.
/// @param piece The @c Piece.
/// @return True if the piece code represents the <em>piece</em>.
/// @throw Never throws.
///
bool
isSame(piece_t code, Piece piece) noexcept;

///
/// @brief Determine if the piece code represents the same <em>color</em>.
/// @param piece The bit pattern reprsenting a piece and its color.
/// @param color The @c Color.
/// @return True if the piece code represents the <em>color</em>.
/// @throw Never throws.
///
bool
isSame(piece_t piece, Color color) noexcept;

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
operator<<(std::ostream &os, Piece piece);

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
operator<<(std::ostream &os, Color color);

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
operator<<(std::ostream &os, PieceMask mask);

///
/// @brief Logical and operator for @c Color and @c Piece.
/// @param color The @c Color.
/// @param piece The @c Piece.
/// @return The bit pattern of ANDing the color and piece.
/// @throw Never throws.
///
piece_t
operator|(Color color, Piece piece) noexcept;

///
/// @brief Logical negation operator for @c Color.
/// @param color The @c Color.
/// @return White if it is black, black if it is white, or none.
/// @throw Never throws.
///
Color
operator~(Color color) noexcept;

///
/// @brief Obtain a short string piece code representing the piece.
/// @param piece The bit code representing the piece and its color.
/// @return A short, 1 to 2 char, string code.
/// @throw Never throws.
///
const char*
shortString(piece_t piece) noexcept;

/////////////////////////////////////////////////////////////////////////////////////
// definitions
/////////////////////////////////////////////////////////////////////////////////////

//
// get the piece value
//
inline Piece
getPiece(piece_t piece) noexcept
{
  piece &= static_cast<piece_t>(PieceMask::PIECE);
  return static_cast<Piece>(piece);
}

//
// get the color value
//
inline Color
getColor(piece_t piece) noexcept
{
  piece &= static_cast<piece_t>(PieceMask::COLOR);
  return static_cast<Color>(piece);
}

//
// check if the piece is a pawn
//
inline bool
isPawn(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::P;
}

//
// check if the piece is a pawn
//
inline bool
isPawn(Piece piece) noexcept
{
  return piece == Piece::P;
}

//
// check if the piece is a knight
//
inline bool
isKnight(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::N;
}

//
// check if the piece is a knight
//
inline bool
isKnight(Piece piece) noexcept
{
  return piece == Piece::N;
}

//
// check if the piece is a bishop
//
inline bool
isBishop(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::B;
}

//
// check if the piece is a bishop
//
inline bool
isBishop(Piece piece) noexcept
{
  return piece == Piece::B;
}

//
// check if the piece is a bishop
//
inline bool
isRook(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::R;
}

//
// check if the piece is a rook
//
inline bool
isRook(Piece piece) noexcept
{
  return piece == Piece::R;
}

//
// checkif the piece is a queen
//
inline bool
isQueen(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::Q;
}

//
// check if the piece is a queen
//
inline bool
isQueen(Piece piece) noexcept
{
  return piece == Piece::Q;
}

//
// check if the piece is a king
//
inline bool
isKing(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::K;
}

//
// check if the piece is a king
//
inline bool
isKing(Piece piece) noexcept
{
  return piece == Piece::K;
}

//
// check if the piece is white
//
inline bool
isWhite(piece_t piece) noexcept
{
  return getColor(piece) == Color::W;
}

//
// check if the color is white
//
inline bool
isWhite(Color color) noexcept
{
  return color == Color::W;
}

//
// check if the color is black
//
inline bool
isBlack(piece_t piece) noexcept
{
  return getColor(piece) == Color::B;
}

//
// check if the color is black
//
inline bool
isBlack(Color color) noexcept
{
  return color == Color::B;
}

//
// check if the piece is NONE
//
inline bool
notPiece(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::NONE;
}

//
// check if the piece is NONE
//
inline bool
notPiece(Piece piece) noexcept
{
  return piece == Piece::NONE;
}

//
// check if color is NONE
//
inline bool
notColor(piece_t piece) noexcept
{
  return getColor(piece) == Color::NONE;
}

//
// check if the piece is NONE
//
inline bool
notColor(Color color) noexcept
{
  return color == Color::NONE;
}

//
// check if piece code contains piece
//
inline bool
isSame(piece_t code, Piece piece) noexcept
{
  return getPiece(code) == piece;
}

//
// check if piece code contains color
//
inline bool
isSame(piece_t piece, Color color) noexcept
{
  return getColor(piece) == color;
}

//
// logical or operator for color and piece to get bit pattern
//
inline piece_t
operator|(Color color, Piece piece) noexcept
{
  return static_cast<piece_t>(color) | static_cast<piece_t>(piece);
}

} // namespace zoor
#endif // _BASICTYPES_H
