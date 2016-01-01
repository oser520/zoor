/**
 * @file square.hh
 * @author Omar A Serrano
 * @data 2015-12-31
 */
#ifndef _SQUARE_H
#define _SQUARE_H

#include <iostream>

namespace zoor {

/**
 * Represents a position in a chess board.
 *
 * A @c Squar is aware of how big is the board, if a row and column are within the
 * bounds of a chess board, and what piece, if any, is sitting on it, including its
 * color.
 */
class Square
{
  /**
   * @copydoc std::ostream& operator<<(std::ostream&, const Square&)
   */
  friend std::ostream& operator<<(std::ostream&, const Square&);

  /**
   * @copydoc bool operator==(const Square&, const Square&)
   */
  friend bool operator==(const Square&, const Square&) noexcept;

public:
  /**
   * Alias for type of row and column.
   */
  using dim_type = unsigned short;

  /**
   * @brief The maximum size of row or column. The dimensions of the chess board.
   */
  static constexpr dim_type BOARD_DIM = 8;

  /**
   * @brief Constructs a @c Square with a specific row and column.
   * @param row The row of the @c Square. Assumption: row <= BOARD_DIM.
   * @param column The column of the @c Square. Assumption: column <= BOARD_DIM.
   */
  Square(dim_type row, dim_type column) noexcept;
  
  /**
   * @brief Default constructor.
   * @throw Does not throw exception.
   */
  Square() noexcept = default

  /**
   * @brief Default copy constructor.
   * @param square The @c Square being copied. 
   * @throw Does not throw exception.
   */
  Square(const Square& square) noexcept = default

  /**
   * @brief Default move constructor.
   * @param square The @c Square being moved. 
   * @throw Does not throw exception.
   */
  Square(Square&& square) noexcept = default

  /**
   * @brief Default copy assignment.
   * @param square The @c Square being copied. 
   * @throw Does not throw exception.
   */
  Square& operator=(const Square& square) noexcept = default

  /**
   * @brief Default move assignment.
   * @param square The @c Square being moved. 
   * @throw Does not throw exception.
   */
  Square& operator=(Square &&square) noexcept = default

  /**
   * @brief Default destructor.
   * @throw Does not throw exception.
   */
  ~Square() noexcept = default;

  /**
   * @brief Gets the row number without modifying the @c Square.
   * @return The row number.
   * @throw Does not throw exception.
   */
  dim_type row() const noexcept;

  /**
   * @brief Gets the column number without modifying the @c Square.
   * @return The column number.
   * @throw Does not throw exception.
   */
  dim_type col() const noexcept;

  
  /**
   * @brief Sets the row number. Enforces the invariant for the row size.
   * @param row The row number.
   * @return A reference to this @c Square
   * @throw Guaranteed not to throw.
   */
  Square& setRow(dim_type row) noexcept;

  /**
   * @brief Sets the column number. Enforces the invariant for the column size.
   * @param column The column number.
   * @return A reference to this @c Square
   * @throw Guaranteed not to throw.
   */
  Square& setCol(dim_type column) noexcept;

private:
  /**
   * The row in the @c Square. Invariant: \f$0 \leq row \le BOARD_DIM.
   */
  dim_type mRow;

  /**
   * The column in the @c Square. Invariant: \f$0 \leq column \le BOARD_DIM.
   */
  dim_type mCol;
};

/**
 * @brief Equality test for @c Square.
 *
 * @param square1 The first @c Square operand.
 * @param square2 The second @c Square operand.
 * @return True if square1 and square2 are equal.
 * @throw Does not throw exception.
 */
bool operator==(const Square& square1, const Square& square2) noexcept;

/**
 * @brief Non-equality test for @c Square.
 *
 * @param square1 The first @c Square operand.
 * @param square2 The second @c Square operand.
 * @return True if square1 and square2 are not equal.
 * @throw Does not throw exception.
 */
bool operator!=(const Square& square1, const Square& square2) noexcept;

/**
 * @brief Output operator for @c Square. Format is <em>{row, column}</em>.
 *
 * @param os The output stream. 
 * @param square An immutable @c Square.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Square& square);

} // namespace zoor

#endif // _SQUARE_H
