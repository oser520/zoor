/**
 * @file square.cc
 * @author Omar A Serrano
 * @data 2015-12-31
 */

namespace zoor {

Square::Square(dim_type row, dim_type column) noexcept
  : mRow(row),
    mCol(column)
{
  assert(mRow < BOARD_DIM);
  assert(mCol < BOARD_DIM);
}


} // namespace zoor
