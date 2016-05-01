/////////////////////////////////////////////////////////////////////////////////////
/// @file basicboard.cc
/// @author Omar A Serrano
/// @date 2016-04-30
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <cassert>

//
// zoor
//
#include "basicboard.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// BoardIter
/////////////////////////////////////////////////////////////////////////////////////

//
// Ctor with pointer param
//
BoardIter(piece_t *piece) noexcept
  : mIter(piece)
{
  assert(mIter != nullptr);
}

//
// prefix increment
//
BoardIter&
operator++() noexcept
{
  assert(mIter != nullptr);
  ++mIter;
  return *this;
}

//
// postfix increment
//
BoardIter
operator++(int) noexcept
{
  assert(mIter != nullptr);
  BoardIter iter(*this);
  ++mIter;
  return iter;
}

//
// prefix decrement
//
BoardIter&
operator--() noexcept
{
  assert(mIter != nullptr);
  --mIter;
  return *this;
}

//
// postfix decrement
//
BoardIter
operator--(int) noexcept
{
  assert(mIter != nullptr);
  BoardIter iter(*this);
  --mIter;
  return iter;
}

//
// dereference operator
//
const BoardIter::reference
operator*() const noexcept
{
  assert(mIter != nullptr);
  return *mIter;
}

//
// addition operator
//
BoardIter
operator+(const BoardIter &iter, BoardIter::difference_type value) noexcept
{
  BoardIter other(iter);
  other += value;
  return other;
}

//
// subtraction operator
//
BoardIter
operator-(const BoardIter &iter, BoardIter::difference_type value) noexcept
{
  BoardIter other(iter);
  other -= value;
  return other;
}

} // zoor
