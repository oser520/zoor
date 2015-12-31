/**
 * @file square.cc
 * @author Omar A Serrano
 * @data 2015-12-31
 */

namespace zoor {

using dim_type = Square::dim_type;

Square::Square(dim_type row, dim_type column) noexcept
  : mRow(row),
    mCol(column)
{
  assert(mRow < BOARD_DIM);
  assert(mCol < BOARD_DIM);
}

dim_type Square::row() const noexcept
{
  return mRow;
}

dim_type Square::col() const noexcept
{
  return mCol;
}

Square& Square::setRow(dim_type row) noexcept
{
  assert(row < BOARD_DIM);
  mRow = row;
  return *this;
}

Square& Square::setCol(dim_type column) noexcept
{
  assert(column < BOARD_DIM);
  mCol = column;
  return *this;
}

bool operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.mRow == square2.mRow && square1.mCol == square2.mCol;
}

bool operator!=(const Square& square1, const Square& square2) noexcept;
{
  return !(square1 == square2);
}

std::ostream& operator<<(std::ostream& os, const Square& square)
{
  os << "(" << square.mRow << ", " << square.mCol << ")";
  return os;
}

} // namespace zoor
