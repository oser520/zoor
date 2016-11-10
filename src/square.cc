////////////////////////////////////////////////////////////////////////////////
//! @file square.cc
//! @author Omar A Serrano
//! @data 2015-12-31
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <ostream>
#include <sstream>
#include <string>

//
// zoor
//
#include "square.hh"

namespace zoor {

//
// get a string representation of the square
//
std::string
Square::toString() const
{
  std::ostringstream oss;
  oss << *this;

  return oss.str();
}

//
// get the hash value for the square
//
size_t
Square::hashCode() const noexcept
{
  // the hash value
  size_t h = 0;

  h += static_cast<size_t>(mPiece);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mColor);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mRow);
  h += h << 10;
  h ^= h >> 6;

  h += static_cast<size_t>(mCol);
  h += h << 10;
  h ^= h >> 6;

  h += h << 3;
  h += h >> 11;
  h += h << 15;

  return h;
}

//
// equality operator
//
bool
operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.piece() == square2.piece()
      and square1.color() == square2.color()
      and square1.row() == square2.row()
      and square1.column() == square2.column();
}

//
// output operator
//
std::ostream&
operator<<(std::ostream& os, const Square& square)
{
  os << "("
     << square.piece() << ", "
     << square.color() << ", "
     << square.row() << ", "
     << square.column()
     << ")";
  return os;
}

} // namespace zoor
