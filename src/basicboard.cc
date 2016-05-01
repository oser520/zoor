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
// add and assign to self
//
BoardIter&
operator+=(difference_type value) noexcept
{
  assert(mIter != nullptr);
  mIter += value;
  return *this;
}

//
// add and subtract to self
//
BoardIter&
operator-=(difference_type value) noexcept
{
  assert(mIter != nullptr);
  mIter -= value;
  return *this;
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

//
// equality operator
//
bool
operator==(const BoardIter &iter1, const BoardIter &iter2) noexcept
{
  assert(iter1.mIter != nullptr);
  assert(iter2.mIter != nullptr);
  return iter1.mIter == iter2.mIter;
}

//
// non-equality operator
//
bool
operator!=(const BoardIter &iter1, const BoardIter &iter2) noexcept
{
  return !(iter1 == iter2);
}

} // zoor
