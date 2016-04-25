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
#include <iostream>
#include <functional>
#include <string>

//
// zoor
//
#include "piececode.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief Represents a position in a chess board.
/// @details A @c Square is aware of how big is the board, if a row and column are
/// within the bounds of a chess board, and what piece, if any, is sitting on it,
/// including its color.
///
class Square
{
public:
  ///
  /// @brief Alias for type of row and column.
  ///
  using dim_type = short;

  ///
  /// @brief The maximum size of row or column. The dimensions of the chess board.
  ///
  static constexpr dim_type BOARD_DIM = 8;

  ///
  /// @brief Constructs a @c Square with a specific row and column. The piece is set
  /// to <em>NONE</em> and the piece color to <em>NONE</em>.
  /// @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
  /// @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
  /// @throw Never throws exception.
  ///
  Square(dim_type row, dim_type column) noexcept;

  ///
  /// @brief Constructs a @c Square with row, column, and piece.
  /// @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
  /// @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
  /// @param code The bit pattern containing the piece and color info.
  /// @throw Never throws exception.
  ///
  Square(dim_type row, dim_type column, piececode_t code) noexcept;

  ///
  /// @brief Constructs a @c Square with a specific row, column, and piece.
  /// @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
  /// @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
  /// @param piece The piece sitting on the @c Square.
  /// @param color The color of the @c PieceCode.
  /// @throw Never throws exception.
  ///
  Square(dim_type row, dim_type column, PieceCode piece, PieceColor color) noexcept;

  ///
  /// @brief Default constructor.
  /// @throw Does not throw exception.
  ///
  Square() noexcept;

  ///
  /// @brief Default copy constructor.
  /// @param square The @c Square being copied.
  /// @throw Does not throw exception.
  ///
  Square(const Square& square) noexcept = default;

  ///
  /// @brief Default move constructor.
  /// @param square The @c Square being moved.
  /// @throw Does not throw exception.
  ///
  Square(Square&& square) noexcept = default;

  ///
  /// @brief Default copy assignment.
  /// @param square The @c Square being copied.
  /// @throw Does not throw exception.
  ///
  Square&
  operator=(const Square& square) noexcept = default;

  ///
  /// @brief Default move assignment.
  /// @param square The @c Square being moved.
  /// @throw Does not throw exception.
  ///
  Square&
  operator=(Square &&square) noexcept = default;

  ///
  /// @brief Default destructor.
  /// @throw Does not throw exception.
  ///
  ~Square() noexcept = default;

  ///
  /// @brief Gets the row number without modifying the @c Square.
  /// @return The row number.
  /// @throw Does not throw exception.
  ///
  dim_type
  row() const noexcept;

  ///
  /// @brief Gets the column number without modifying the @c Square.
  /// @return The column number.
  /// @throw Does not throw exception.
  ///
  dim_type
  column() const noexcept;

  ///
  /// @brief Gets the piece without modifying the @c Square.
  /// @return The piece code.
  /// @throw Does not throw exception.
  ///
  PieceCode
  piece() const noexcept;

  ///
  /// @brief Gets the piece color without modifying the @c Square.
  /// @return The piece color.
  /// @throw Does not throw exception.
  ///
  PieceColor
  color() const noexcept;

  ///
  /// @brief Gets the bit pattern of the piece and color.
  /// @return The piece code.
  /// @throw Never throws.
  ///
  piececode_t
  code() const noexcept;

  ///
  /// @brief Sets the row number. Enforces the invariant for the row size.
  /// @param row The row number.
  /// @return A reference to this @c Square
  /// @throw Guaranteed not to throw.
  ///
  Square&
  setRow(dim_type row) noexcept;

  ///
  /// @brief Sets the column number. Enforces the invariant for the column size.
  /// @param column The column number.
  /// @return A reference to this @c Square
  /// @throw Guaranteed not to throw.
  ///
  Square&
  setColumn(dim_type column) noexcept;

  ///
  /// @brief Sets the piece.
  /// @param The piece.
  /// @return A reference to this @c Square.
  /// @throw Does not throw exception.
  ///
  Square&
  setPiece(PieceCode piece) noexcept;

  ///
  /// @brief Sets the piece color.
  /// @param The piece color.
  /// @return A reference to this @c Square.
  /// @throw Does not throw exception.
  ///
  Square&
  setColor(PieceColor color) noexcept;

  ///
  /// @brief Sets the piece and color.
  /// @param code The piece code with piece and color info.
  /// @return A reference to this @c Square.
  /// @throw Does not throw exception.
  ///
  Square&
  setPieceCode(piececode_t code) noexcept;

  ///
  /// @brief Sets the row and column.
  /// @param row The row in the board.
  /// @param column The column in the board.
  /// @return A reference to this @c Square.
  /// @throw Never throws.
  ///
  Square&
  setLocation(dim_type row, dim_type column) noexcept;

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

  ///
  /// @brief Check if the position is in the board.
  /// @param position The position in the board.
  /// @param column The column in the board.
  /// @return True if the position is in the board.
  /// @throw Never throws.
  ///
  static bool
  isInBound(dim_type position) noexcept;

  ///
  /// @brief Check if the row and column are in the board.
  /// @param row The row in the board.
  /// @param column The column in the board.
  /// @return True if the row and column are in the board.
  /// @throw Never throws.
  ///
  static bool
  isInBound(dim_type row, dim_type column) noexcept;

private:
  // The piece sitting on this @c Square, which may be <em>NONE</em>.
  PieceCode mPiece;

  // The color of the piece sitting on this @c Square. Only meaningful if
  // there is a piece on it.
  PieceColor mColor;

  // The row in the @c Square. Invariant: \f$0 \leq row \le BOARD_DIM.
  dim_type mRow;

  // The column in the @c Square. Invariant: \f$0 \leq column \le BOARD_DIM.
  dim_type mColumn;
};

///
/// @brief Equality test for @c Square.
/// @param square1 The first @c Square operand.
/// @param square2 The second @c Square operand.
/// @return True if square1 and square2 are equal.
/// @throw Does not throw exception.
///
bool
operator==(const Square& square1, const Square& square2) noexcept;

///
/// @brief Non-equality test for @c Square.
/// @param square1 The first @c Square operand.
/// @param square2 The second @c Square operand.
/// @return True if square1 and square2 are not equal.
/// @throw Does not throw exception.
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

//
// get the row
//
inline Square::dim_type
Square::row() const noexcept
{
  return mRow;
}

//
// get the column
//
inline Square::dim_type
Square::column() const noexcept
{
  return mColumn;
}

//
// get the piece type
//
inline PieceCode
Square::piece() const noexcept
{
  return mPiece;
}

//
// get the piece color
//
inline PieceColor
Square::color() const noexcept
{
  return mColor;
}

//
// get the bit code for the piece and color
//
inline piececode_t
Square::code() const noexcept
{
  return mColor | mPiece;
}

//
// set the row
//
inline Square&
Square::setRow(dim_type row) noexcept
{
  assert(isInBound(row));
  mRow = row;
  return *this;
}

//
// set the column
//
inline Square&
Square::setColumn(dim_type column) noexcept
{
  assert(isInBound(column));
  mColumn = column;
  return *this;
}

//
// set the piece
//
inline Square&
Square::setPiece(PieceCode piece) noexcept
{
  mPiece = piece;
  return *this;
}

//
// set the color
//
inline Square&
Square::setColor(PieceColor color) noexcept
{
  mColor = color;
  return *this;
}

//
// check if position is valid
//
inline bool
Square::isInBound(dim_type position) noexcept
{
  return position >= 0 && position < BOARD_DIM;
}

//
// check if row and column are valid
//
inline bool
Square::isInBound(dim_type row, dim_type column) noexcept
{
  return row >= 0 && row < BOARD_DIM
      && column >= 0 && column < BOARD_DIM;
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
