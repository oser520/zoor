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

} // namespace zoor
