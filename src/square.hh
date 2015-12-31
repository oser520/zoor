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
 * @brief Represents a position in a chess board. It is aware of how big the board
 * is, and whether a given position is within the bounds of the board.
 */
class Square
{
  friend std::ostream& operator<<(std::ostream&, const Square&);
  friend bool operator==(const Square&, const Square&) noexcept;

public:
  using dim_type = unsigned short;
  static constexpr dim_type BOARD_DIM = 8;

  // custom constructor
  Square(dim_type, dim_type);
  
  // standard copy control
  Square() noexcept = default
  Square(const Square&) noexcept = default
  Square(Square&&) noexcept = default
  Square& operator=(const Square&) noexcept = default
  Square& operator=(Square&&) noexcept = default
  ~Square() noexcept = default;

  // getters
  dim_type row() const noexcept;
  dim_type col() const noexcept;

  // setters
  Square& setRow(dim_type) noexcept;
  Square& setCol(dim_type) noexcept;

private:
  dim_type mRow;
  dim_type mCol;
};

/**
 * @brief Output operator for Square. Format is <em>{row, column}</em>.
 *
 * @param os The output stream. 
 * @param square An immutable squre.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Square& square);

/**
 * @brief Equality test for Square.
 *
 * @param square1 The first square operand.
 * @param square2 The second square operand.
 * @return True if square1 and square2 are equal.
 * @except Does not throw exception.
 */
bool operator==(const Square& square1, const Square& square2) noexcept;

/**
 * @brief Non-equality test for Square.
 *
 * @param square1 The first square operand.
 * @param square2 The second square operand.
 * @return True if square1 and square2 are not equal.
 * @except Does not throw exception.
 */
bool operator!=(const Square& square1, const Square& square2) noexcept;

} // namespace zoor

#endif // _SQUARE_H
