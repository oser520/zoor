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
 * Represents a position in the baord.
 */
class Square
{
  friend std::ostream& operator<<(std::ostream&, const Square&);
  friend bool operator==(const Square&, const Square&) noexcept;

public:
  using dim_type = unsigned short;
  static constexpr dim_type BOARD_DIM = 8;
  
  // standard copy control
  Square() noexcept = default
  Square(const Square&) noexcept = default
  Square(Square&&) noexcept = default
  Square& operator=(const Square&) noexcept = default
  Square& operator=(Square&&) noexcept = default
  ~Square() noexcept = default;
  // custom constructor
  Square(dim_type, dim_type);

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

} // namespace zoor

#endif // _SQUARE_H
