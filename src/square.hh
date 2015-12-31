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
  /**
   * Alias for type of row and column.
   */
  using dim_type = unsigned short;

  /**
   * @brief The maximum size of row or column. The dimensions of the chess board.
   */
  static constexpr dim_type BOARD_DIM = 8;

  /**
   * @brief Constructs square with specific with specific row and column.
   * @param row The row of the square.
   * @param column The column of the square.
   * @except Throws exception if row or column are not within bounds of
   *  <em>BOARD_DIM</em>.
   */
  Square(dim_type row, dim_type column);
  
  /**
   * @brief Default constructor.
   * @except Does not throw exception.
   */
  Square() noexcept = default

  /**
   * @brief Default copy constructor.
   * @param square The square being copied. 
   * @except Does not throw exception.
   */
  Square(const Square& square) noexcept = default

  /**
   * @brief Default move constructor.
   * @param square The square being moved. 
   * @except Does not throw exception.
   */
  Square(Square&& square) noexcept = default

  /**
   * @brief Default copy assignment.
   * @param square The square being copied. 
   * @except Does not throw exception.
   */
  Square& operator=(const Square& square) noexcept = default

  /**
   * @brief Default move assignment.
   * @param square The square being moved. 
   * @except Does not throw exception.
   */
  Square& operator=(Square &&square) noexcept = default

  /**
   * @brief Default destructor.
   * @except Does not throw exception.
   */
  ~Square() noexcept = default;

  /**
   * @brief Gets the row number without modifying the square.
   * @return The row number.
   * @except Does not throw exception.
   */
  dim_type row() const noexcept;

  /**
   * @brief Gets the column number without modifying the square.
   * @return The column number.
   * @except Does not throw exception.
   */
  dim_type col() const noexcept;

  // setters
  Square& setRow(dim_type);
  Square& setCol(dim_type);

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
