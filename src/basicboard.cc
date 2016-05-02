/////////////////////////////////////////////////////////////////////////////////////
/// @file basicboard.cc
/// @author Omar A Serrano
/// @date 2016-04-30
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

//
// zoor
//
#include "basicboard.hh"

namespace zoor {

//
// init static vars
//
const piece_t BasicBoard::INIT_BOARD[] = {
// a     b     c     d     e     f     g     h
  0x0c, 0x0a, 0x0b, 0x0d, 0x0e, 0x0b, 0x0a, 0x0c, // 1
  0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, // 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 3
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 4
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 5
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 6
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, // 7
  0x14, 0x12, 0x13, 0x15, 0x16, 0x13, 0x12, 0x14  // 8
};

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
  return &(*iter1) == &(*iter2);
}

//
// non-equality operator
//
bool
operator!=(const BoardIter &iter1, const BoardIter &iter2) noexcept
{
  return !(iter1 == iter2);
}

/////////////////////////////////////////////////////////////////////////////////////
// BasicBoard
/////////////////////////////////////////////////////////////////////////////////////

//
// Default ctor.
//
BasicBoard::BasicBoard()
  : mArr(new piece_t[64])
{
  std::copy(std::begin(INIT_BOARD), std::end(INIT_BOARD), begin());
}

//
// Copy ctor.
//
BasicBoard::BasicBoard(const BasicBoard &board)
  : mArr(new piece_t[64])
{
  std::copy(board.begin(), board.end(), begin());
}

//
// Move ctor.
//
BasicBoard::BasicBoard(BasicBoard &&board)
  : mArr(board.mArr)
{
  board.mArr = nullptr;
}

//
// Copy Assignment.
//
BasicBoard&
BasicBoard::operator=(const BasicBoard &board) noexcept
{
  std::copy(board.begin(), board.end(), begin());
  return *this;
}

//
// Move assignment.
//
BasicBoard&
BasicBoard::operator=(BasicBoard &&board) noexcept
{
  std::swap(mArr, board.mArr);
  return *this;
}

//
// Dtor.
//
BasicBoard::~BasicBoard() noexcept
{
  if (mArr != nullptr)
    delete[] mArr;
}

//
// get the piece from a given square
//
piece_t
BasicBoard::get(dim_t row, dim_t column) const noexcept
{
  assert(inBoard(row, column));
  return mArr[index(row, column)];
}

//
// clear the contents of a square
//
void
BasicBoard::clear(dim_t row, dim_t column) noexcept
{
  assert(inBoard(row, column));
  mArr[index(row, column)] = 0;
}

//
// put a piece on a square
//
void
BasicBoard::put(dim_t row, dim_t column, piece_t piece) noexcept
{
  assert(inBoard(row, column));
  mArr[index(row, column)] = piece;
}

//
// put a piece on a square
//
void
BasicBoard::put(dim_t row, dim_t column, Piece piece, Color color) noexcept
{
  assert(inBoard(row, column));
  mArr[index(row, column)] = color | piece;
}

} // zoor
