/////////////////////////////////////////////////////////////////////////////////////
/// @file square.hh
/// @author Omar A Serrano
/// @data 2015-12-31
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _SQUARE_H
#define _SQUARE_H

//
// STL
//
#include <cassert>
#include <ostream>
#include <functional>
#include <string>
#include <utility>

//
// zoor
//
#include "basictypes.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief Represents a position on a chess board.
/// @details A @c Square is aware of how big the board is, if a row and column are
/// within the bounds of a chess board, and what piece, if any, is sitting on it,
/// including its color.
///
class Square
{
public:
  ///
  /// @brief Constructs a @c Square with a specific row and column. The piece is set
  /// to <em>NONE</em> and the piece color to <em>NONE</em>.
  /// @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
  /// @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
  /// @throw Never throws.
  ///
  Square(dim_t row, dim_t column) noexcept;

  ///
  /// @brief Constructs a @c Square with row, column, and piece.
  /// @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
  /// @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
  /// @param code The bit pattern containing the piece and color info.
  /// @throw Never throws.
  ///
  Square(dim_t row, dim_t column, piece_t code) noexcept;

  ///
  /// @brief Constructs a @c Square with a specific row, column, and piece.
  /// @param row The row of the @c Square. Assumption: row <= DIM.
  /// @param column The column of the @c Square. Assumption: column <= DIM.
  /// @param piece The piece sitting on the @c Square.
  /// @param color The @c Color.
  /// @throw Never throws.
  ///
  Square(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @brief Default constructor.
  /// @throw Never throws.
  ///
  Square() noexcept;

  ///
  /// @brief Default copy constructor.
  /// @param square The @c Square being copied.
  /// @throw Never throws.
  ///
  Square(const Square& square) noexcept = default;

  ///
  /// @brief Default move constructor.
  /// @param square The @c Square being moved.
  /// @throw Never throws.
  ///
  Square(Square&& square) noexcept = default;

  ///
  /// @brief Default copy assignment.
  /// @param square The @c Square being copied.
  /// @throw Never throws.
  ///
  Square&
  operator=(const Square& square) noexcept = default;

  ///
  /// @brief Default move assignment.
  /// @param square The @c Square being moved.
  /// @throw Never throws.
  ///
  Square&
  operator=(Square &&square) noexcept = default;

  ///
  /// @brief Default destructor.
  /// @throw Never throws.
  ///
  ~Square() noexcept = default;

  ///
  /// @brief Gets the row number without modifying the @c Square.
  /// @return The row number.
  /// @throw Never throws.
  ///
  dim_t
  row() const noexcept;

  ///
  /// @brief Gets the column number without modifying the @c Square.
  /// @return The column number.
  /// @throw Never throws.
  ///
  dim_t
  column() const noexcept;

  ///
  /// @brief Gets the piece without modifying the @c Square.
  /// @return The @c Piece.
  /// @throw Never throws.
  ///
  Piece
  piece() const noexcept;

  ///
  /// @brief Gets the piece color without modifying the @c Square.
  /// @return The @c Color.
  /// @throw Never throws.
  ///
  Color
  color() const noexcept;

  ///
  /// @brief Gets the bit pattern of the piece and color.
  /// @return The piece code.
  /// @throw Never throws.
  ///
  piece_t
  code() const noexcept;

  ///
  /// @brief Get the row and column.
  /// @return A pair with first=row and second=column.
  /// @throw Never throws.
  ///
  std::pair<dim_t, dim_t>
  location() const noexcept;

  ///
  /// @brief Sets the row number. Enforces the invariant for the row size.
  /// @param row The row number.
  /// @return A reference to this @c Square
  /// @throw Never throws.
  ///
  Square&
  row(dim_t row) noexcept;

  ///
  /// @brief Sets the column number.
  /// @param column The column number.
  /// @return A reference to this @c Square
  /// @throw Never throws.
  ///
  Square&
  column(dim_t column) noexcept;

  ///
  /// @brief Sets the piece.
  /// @param piece The @c Piece.
  /// @return A reference to this @c Square.
  /// @throw Never throws.
  ///
  Square&
  piece(Piece piece) noexcept;

  ///
  /// @brief Sets the piece color.
  /// @param color The @c Color.
  /// @return A reference to this @c Square.
  /// @throw Never throws.
  ///
  Square&
  color(Color color) noexcept;

  ///
  /// @brief Sets the piece and color.
  /// @param code The piece code with piece and color info.
  /// @return A reference to this @c Square.
  /// @throw Never throws.
  ///
  Square&
  code(piece_t code) noexcept;

  ///
  /// @brief Sets the row and column.
  /// @param row The row in the board.
  /// @param column The column in the board.
  /// @return A reference to this @c Square.
  /// @throw Never throws.
  ///
  Square&
  location(dim_t row, dim_t column) noexcept;

  ///
  /// @brief Get the string representation of the square.
  /// @return A string representing the square.
  ///
  std::string
  toString() const;

  ///
  /// @brief Get the hash code for the square.
  /// @return The hash code.
  /// @throw Never throws.
  ///
  size_t
  hashCode() const noexcept;

private:
  // The piece sitting on this @c Square.
  Piece mPiece;

  // The piece sitting on this @c Square.
  Color mColor;
 
  // The row.
  unsigned char mRow;

  // The column.
  unsigned char mCol;
};

///
/// @brief Equality test for @c Square.
/// @param square1 The first @c Square operand.
/// @param square2 The second @c Square operand.
/// @return True if square1 and square2 are equal.
/// @throw Never throws.
///
bool
operator==(const Square& square1, const Square& square2) noexcept;

///
/// @brief Non-equality test for @c Square.
/// @param square1 The first @c Square operand.
/// @param square2 The second @c Square operand.
/// @return True if square1 and square2 are not equal.
/// @throw Never throws.
///
bool
operator!=(const Square& square1, const Square& square2) noexcept;

///
/// @brief Output operator for @c Square. Format is
/// <em>(piece, color, row, column)</em>.
/// @param os The output stream.
/// @param square An immutable @c Square.
/// @return A reference to the output stream.
///
std::ostream&
operator<<(std::ostream& os, const Square& square);

/////////////////////////////////////////////////////////////////////////////////////
// definitions
/////////////////////////////////////////////////////////////////////////////////////

//
// default ctor
//
inline
Square::Square() noexcept
  : mPiece(Piece::NONE),
    mColor(Color::NONE),
    mRow(),
    mCol() {}

//
// two param ctor
//
inline
Square::Square(dim_t row, dim_t column) noexcept
  : mPiece(Piece::NONE),
    mColor(Color::NONE),
    mRow(row),
    mCol(column)
{
  assert(checkDim(row, column, BOARD_DIM));
}

//
// three param ctor
//
inline
Square::Square(dim_t row, dim_t column, piece_t code) noexcept
  : mPiece(getPiece(code)),
    mColor(getColor(code)),
    mRow(row),
    mCol(column)
{
  assert(checkDim(row, column, BOARD_DIM));
}

//
// 4 param ctor
//
inline
Square::Square(dim_t row, dim_t column, Piece piece, Color color) noexcept
  : mPiece(piece),
    mColor(color),
    mRow(row),
    mCol(column)
{
  assert(checkDim(row, column, BOARD_DIM));
}

//
// get the row
//
inline Square::dim_t
Square::row() const noexcept
{
  return static_cast<dim_t>(mRow);
}

//
// get the column
//
inline Square::dim_t
Square::column() const noexcept
{
  return static_cast<dim_t>(mCol);
}

//
// get the piece type
//
inline Piece
Square::piece() const noexcept
{
  return mPiece;
}

//
// get the piece color
//
inline Color
Square::color() const noexcept
{
  return mColor;
}

//
// get the bit code for the piece and color
//
inline piece_t
Square::code() const noexcept
{
  return mColor | mPiece;
}

//
// get the row and column
//
inline std::pair<dim_t, dim_t>
Square::location() const noexcept
{
  return std::make_pair(mRow, mCol);
}

//
// set the row
//
inline Square&
Square::row(dim_t row) noexcept
{
  assert(checkDim(row, BOARD_DIM));
  mRow = static_cast<unsigned char>(row);
  return *this;
}

//
// set the column
//
inline Square&
Square::column(dim_t column) noexcept
{
  assert(checkDim(column, BOARD_DIM));
  mCol = static_cast<unsigned char>(column);
  return *this;
}

//
// set the piece
//
inline Square&
Square::piece(Piece piece) noexcept
{
  mPiece = piece;
  return *this;
}

//
// set the color
//
inline Square&
Square::color(Color color) noexcept
{
  mColor = color;
  return *this;
}

//
// set the piece and color
//
inline Square&
Square::code(piece_t piece) noexcept
{
  mPiece = getPiece(piece);
  mColor = getColor(piece);
  return *this;
}

//
// set the row and column
//
inline Square&
Square::location(dim_t row, dim_t column) noexcept
{
  assert(checkDim(row, column, BOARD_DIM));
  mRow = row;
  mCol = column
  return *this;
}

//
// non-equality operator
//
inline bool
operator!=(const Square& square1, const Square& square2) noexcept
{
  return !(square1 == square2);
}

} // namespace zoor

namespace std {

///
/// @brief Square specialization for <em>hash</em>. Needs to be defined within std
/// namespece.
///
template<>
struct hash<zoor::Square>
{
  using argument_type = zoor::Square;
  using result_type = size_t;

  result_type operator()(const argument_type& arg) const noexcept
  {
    return arg.hashCode();
  }
};

} // std
#endif // _SQUARE_H
