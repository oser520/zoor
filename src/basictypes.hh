////////////////////////////////////////////////////////////////////////////////
//! @file basictypes.hh
//! @author Omar A Serrano
//! @date 2016-04-30
////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICTYPES_H
#define _BASICTYPES_H

//
// STL
//
#include <cstdint>
#include <ostream>

namespace zoor {

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Represents a chess piece and its color
using piece_t = uint8_t;

//! @brief The type used for the dimension of a board.
using dim_t = int16_t;

//! @brief Represents a piece on the board.
//! @details Since each piece on a board is represented in a byte, the type for
//! each Piece is an unsigned char.
//! @li NONE is no piece
//! @li P for pawn
//! @li N for knight
//! @li B for bishop
//! @li R for rook
//! @li Q for queen
//! @li K for king
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

//! @brief Represents the color of a piece.
//! @details The Color can be logically ORed with a Piece to make a piece have
//! color.
//! @li NONE is no color
//! @li W for white
//! @li B for black
enum class Color: piece_t
{
  NONE,       // 0b00000
  W = 1 << 3, // 0b01000
  B = 1 << 4  // 0b10000
};

//! @brief A mask to get the Piece and Color from a bit pattern that contains
//! both.
enum class PieceMask: piece_t
{
  PIECE = 7, // 0b00111
  COLOR = 24 // 0b11000
};

//! @brief A board's row numbers.
enum Row : dim_t
{
  R1, R2, R3, R4, R5, R6, R7, R8
};

//! @brief A board's column letters.
enum Column : dim_t
{
  A, B, C, D, E, F, G, H
};

//
// Functions to extract the Piece and Color from a piece code.
//

Piece
getPiece(piece_t piece) noexcept;

Color
getColor(piece_t piece) noexcept;

//
// Functions to test whether a piece code or Piece is a given type of piece.
//

bool
isPawn(piece_t piece) noexcept;

bool
isPawn(Piece piece) noexcept;

bool
isKnight(piece_t piece) noexcept;

bool
isKnight(Piece piece) noexcept;

bool
isBishop(piece_t piece) noexcept;

bool
isBishop(Piece piece) noexcept;

bool
isRook(piece_t piece) noexcept;

bool
isRook(Piece piece) noexcept;

bool
isQueen(piece_t piece) noexcept;

bool
isQueen(Piece piece) noexcept;

bool
isKing(piece_t piece) noexcept;

bool
isKing(Piece piece) noexcept;

//
// Functions to test the color of a piece.
//

bool
isWhite(piece_t piece) noexcept;

bool
isWhite(Color color) noexcept;

bool
isBlack(piece_t piece) noexcept;

bool
isBlack(Color color) noexcept;

//
// Functions to test if a piece code or Piece is Piece::NONE.
//

bool
notPiece(piece_t piece) noexcept;

bool
notPiece(Piece piece) noexcept;

//
// Functions to test if a piece code or Color is Color::NONE.
//

bool
notColor(piece_t piece) noexcept;

bool
notColor(Color color) noexcept;

//
// Functions to test if a Piece or Color is embedded in a piece code.
//

bool
isSame(piece_t code, Piece piece) noexcept;

bool
isSame(piece_t piece, Color color) noexcept;

//
// Output functions.
//

std::ostream&
operator<<(std::ostream &os, Piece piece);

std::ostream&
operator<<(std::ostream &os, Color color);

std::ostream&
operator<<(std::ostream &os, PieceMask mask);

// Combine color and piece
piece_t
operator|(Color color, Piece piece) noexcept;

// Get opposite color.
Color
operator~(Color color) noexcept;

// Get a string code.
const char*
shortString(piece_t piece) noexcept;

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Get a @c Piece from a bit pattern.
//! @param piece The bit pattern containing a @c Piece.
//! @return A @c Piece.
//! @throw Never throws.
inline Piece
getPiece(piece_t piece) noexcept
{
  piece &= static_cast<piece_t>(PieceMask::PIECE);
  return static_cast<Piece>(piece);
}

//! @brief Get a @c Color from a bit pattern.
//! @param piece The bit pattern containing a @c Color.
//! @return A @c Color.
//! @throw Never throws.
inline Color
getColor(piece_t piece) noexcept
{
  piece &= static_cast<piece_t>(PieceMask::COLOR);
  return static_cast<Color>(piece);
}

//! @brief Determine if the piece code represents a pawn.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a pawn.
//! @throw Never throws.
inline bool
isPawn(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::P;
}

//! @brief Determine if piece is a pawn.
//! @param piece The @c Piece.
//! @return True if piece is a pawn.
//! @throw Never throws.
inline bool
isPawn(Piece piece) noexcept
{
  return piece == Piece::P;
}

//! @brief Determine if the piece code represents a knight.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a knight.
//! @throw Never throws.
inline bool
isKnight(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::N;
}

//! @brief Determine if piece is a knight.
//! @param piece The @c Piece.
//! @return True if piece is a knight.
//! @throw Never throws.
inline bool
isKnight(Piece piece) noexcept
{
  return piece == Piece::N;
}

//! @brief Determine if the piece code represents a bishop.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a bishop.
//! @throw Never throws.
inline bool
isBishop(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::B;
}

//! @brief Determine if piece is a bishop.
//! @param piece The @c Piece.
//! @return True if piece is a bishop.
//! @throw Never throws.
inline bool
isBishop(Piece piece) noexcept
{
  return piece == Piece::B;
}

//! @brief Determine if the piece code represents a rook.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a rook.
//! @throw Never throws.
inline bool
isRook(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::R;
}

//! @brief Determine if piece is a rook.
//! @param piece The @c Piece.
//! @return True if piece is a rook.
//! @throw Never throws.
inline bool
isRook(Piece piece) noexcept
{
  return piece == Piece::R;
}

//! @brief Determine if the piece code represents a queen.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a queen.
//! @throw Never throws.
inline bool
isQueen(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::Q;
}

//! @brief Determine if piece is a queen.
//! @param piece The @c Piece.
//! @return True if piece is a queen.
//! @throw Never throws.
inline bool
isQueen(Piece piece) noexcept
{
  return piece == Piece::Q;
}

//! @brief Determine if the piece code represents a king.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a king.
//! @throw Never throws.
inline bool
isKing(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::K;
}

//! @brief Determine if piece is a king.
//! @param piece The @c Piece.
//! @return True if piece is a king.
//! @throw Never throws.
inline bool
isKing(Piece piece) noexcept
{
  return piece == Piece::K;
}

//! @brief Determine if the piece code represents a piece with white color.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a white piece.
//! @throw Never throws.
inline bool
isWhite(piece_t piece) noexcept
{
  return getColor(piece) == Color::W;
}

//! @brief Determine if the color is white.
//! @param color The @c Color.
//! @return True if the color is white.
//! @throw Never throws.
inline bool
isWhite(Color color) noexcept
{
  return color == Color::W;
}

//! @brief Determine if the piece code represents a piece with black color.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents a black piece.
//! @throw Never throws.
inline bool
isBlack(piece_t piece) noexcept
{
  return getColor(piece) == Color::B;
}

//! @brief Determine if the color is black.
//! @param color The @c Color.
//! @return True if the color is black.
//! @throw Never throws.
inline bool
isBlack(Color color) noexcept
{
  return color == Color::B;
}

//! @brief Determine if the piece code represents a piece, such as a pawn.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents does not represent Piece::NONE,
//! false otherwise.
//! @throw Never throws.
inline bool
isPiece(piece_t piece) noexcept
{
  return getPiece(piece) != Piece::NONE;
}

//! @brief Determine if the piece is a valid piece, such as a pawn.
//! @param piece The Piece.
//! @return True if piece is not Piece::NONE, false otherwise.
//! @throw Never throws.
inline bool
isPiece(Piece piece) noexcept
{
  return piece != Piece::NONE;
}

//! @brief Determine if the piece code represents a <em>Piece::NONE</em>.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents <em>Piece::NONE</em>.
//! @throw Never throws.
inline bool
notPiece(piece_t piece) noexcept
{
  return getPiece(piece) == Piece::NONE;
}

//! @brief Determine if the piece is <em>Piece::NONE</em>.
//! @param piece The @c Piece.
//! @return True if piece is <em>Piece::NONE</em>.
//! @throw Never throws.
inline bool
notPiece(Piece piece) noexcept
{
  return piece == Piece::NONE;
}

//! @brief Determine if the piece code represents a <em>Color::NONE</em>.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @return True if the piece code represents <em>Color::NONE</em>.
//! @throw Never throws.
inline bool
notColor(piece_t piece) noexcept
{
  return getColor(piece) == Color::NONE;
}

//! @brief Determine if the color is <em>Color::NONE</em>.
//! @param color The @c Color.
//! @return True if piece is <em>Color::NONE</em>.
//! @throw Never throws.
inline bool
notColor(Color color) noexcept
{
  return color == Color::NONE;
}

//! @brief Determine if the piece code represents the same <em>piece</em>.
//! @param code The bit pattern reprsenting a piece and its color.
//! @param piece The Piece.
//! @return True if the piece code represents the <em>piece</em>.
//! @throw Never throws.
inline bool
isSame(piece_t code, Piece piece) noexcept
{
  return getPiece(code) == piece;
}

//! @brief Determine if the piece code represents the same <em>color</em>.
//! @param piece The bit pattern reprsenting a piece and its color.
//! @param color The @c Color.
//! @return True if the piece code represents the <em>color</em>.
//! @throw Never throws.
inline bool
isSame(piece_t piece, Color color) noexcept
{
  return getColor(piece) == color;
}

//! @brief Logical and operator for @c Color and @c Piece.
//! @param color The @c Color.
//! @param piece The @c Piece.
//! @return The bit pattern of ANDing the color and piece.
//! @throw Never throws.
inline piece_t
operator|(Color color, Piece piece) noexcept
{
  return static_cast<piece_t>(color) | static_cast<piece_t>(piece);
}

//! @param color The color of the piece.
//! @return 1 if it is white, -1 otherwise.
//! @throw Never throws.
inline dim_t
delta(Color color) noexcept
{
  return isWhite(color) ? 1 : -1;
}

//! @param row The row of the square.
//! @param col The column of the square.
//! @return True if the square is inside of a 8x8 board, false otherwise.
//! @throw Never throws.
inline bool
inBound(dim_t row, dim_t col) noexcept
{
  return row >= 0 and row <= 7
      and col >= 0 and col <= 7;
}

} // namespace zoor
#endif // _BASICTYPES_H
