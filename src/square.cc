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

} // namespace zoor
