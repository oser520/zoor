////////////////////////////////////////////////////////////////////////////////
//! @file basicboard.hh
//! @author Omar A Serrano
//! @date 2016-04-28
////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICBOARD_H
#define _BASICBOARD_H

//
// STL
//
#include <algorithm>
#include <cassert>
#include <utility>

//
// zoor
//
#include "basictypes.hh"

namespace zoor {

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

namespace {
// @brief Compute index from row and column.
// @param row The row number.
// @param column The column number.
// @return The index of the square in range [1, 64].
// @throw Never throws.
dim_t
index(dim_t row, dim_t column) noexcept;
} // namespace

//!
//! @brief A simple board that represents the position in a chess board.
//!
class BasicBoard
{
public:
  //! @brief The number of squares per row and column.
  static constexpr dim_t DIM = 8;

  //! @brief The number of squares in a BasicBoard.
  static constexpr dim_t SIZE = 64;

  //! @brief The default initialization board.
  static const piece_t INIT_BOARD[SIZE];

  //! @brief Alias for iterator.
  using iterator = piece_t*;

  //! @brief Alias for const_iterator.
  using const_iterator = const piece_t*;

  //! @details Initializes the board with the normal setup for beginning game.
  //! @throw May throw bad memory allocation.
  BasicBoard();

  //! @brief Copy ctor.
  //! @param board The board to be copied.
  //! @throw May throw bad memory allocation.
  BasicBoard(const BasicBoard &board);

  //! @brief Move ctor.
  //! @param board The board being moved.
  //! @throw Never throws.
  BasicBoard(BasicBoard &&board) noexcept;

  //! @brief Copy assignment.
  //! @param board The board being assigned.
  //! @return A reference to @c BasicBoard.
  //! @throw Never throws.
  BasicBoard&
  operator=(const BasicBoard &board) noexcept;

  //! @brief Move assignment.
  //! @param board The board being moved.
  //! @return A reference to @c BasicBoard.
  //! @throw Never throws.
  BasicBoard&
  operator=(BasicBoard &&board) noexcept;

  //! @brief Dtor.
  //! @throw Never throws.
  ~BasicBoard() noexcept;

  //! @brief Obtain the contents of a given square.
  //! @param row The row of the square.
  //! @param column The column of the square.
  //! @return The piece located at the given square.
  //! @throw Never throws.
  piece_t
  get(dim_t row, dim_t column) const noexcept;

  //! @brief Clear the contents of a given square.
  //! @param row The row of the square.
  //! @param column The column of the square.
  //! @throw Never throws.
  void
  clear(dim_t row, dim_t column) noexcept;

  //! @brief Put a chess piece on a square.
  //! @param row The row of the square.
  //! @param column The column of the square.
  //! @param piece The type of chess piece.
  //! @throw Never throws.
  void
  put(dim_t row, dim_t column, piece_t piece) noexcept;

  //! @brief Put a chess piece on a square.
  //! @param row The row of the square.
  //! @param column The column of the square.
  //! @param piece The type of chess piece.
  //! @param color The color of the chess piece.
  //! @throw Never throws.
  void
  put(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  //! @brief Get iterator to the first square on the board.
  //! @throw Never throws.
  iterator
  begin() const noexcept;

  //! @brief Get iterator to one past the last square.
  //! @throw Never throws.
  iterator
  end() const noexcept;

  //! @brief Get read only iterator to the first square on the board.
  //! @throw Never throws.
  const_iterator
  cbegin() const noexcept;

  //! @brief Get read only iterator to one past the last square.
  //! @throw Never throws.
  const_iterator
  cend() const noexcept;

  //! @brief Check that row and column are less than BasicBoard::DIM.
  //! @param row The row number.
  //! @brief column The column number.
  //! @return True if both row and column are in the board, false otherwise.
  //! @throw Never throws.
  static bool
  inBoard(dim_t row, dim_t column) noexcept;

  //! @return Return a board without any pieces.
  static BasicBoard
  emptyBoard();

private:
  // Dummy type to indicate to compiler to construct empty board.
  enum class InitEmpty { INIT };

  // Return a board without any pieces.
  BasicBoard(InitEmpty);

  // Pointer to the array.
  piece_t *mArr;

};

//! @brief Equality operator for two boards.
//! @param board1 The left hand board.
//! @param board2 The right hand board.
//! @return True if the board are equal, false otherwise.
//! @throw Never throws.
bool
operator==(const BasicBoard &board1, const BasicBoard &board2) noexcept;

//! @brief Non-equality operator for two boards.
//! @param board1 The left hand board.
//! @param board2 The right hand board.
//! @return False if the board are equal, true otherwise.
//! @throw Never throws.
bool
operator!=(const BasicBoard &board1, const BasicBoard &board2) noexcept;

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

namespace {
//
// compute index of square
//
inline dim_t
index(dim_t row, dim_t column) noexcept
{
  return (row * BasicBoard::DIM) + column;
}
} // namespace

//
// Default ctor.
//
inline
BasicBoard::BasicBoard()
  : mArr(new piece_t[64])
{
  std::copy(std::begin(INIT_BOARD), std::end(INIT_BOARD), begin());
}

//
// Copy ctor.
//
inline
BasicBoard::BasicBoard(const BasicBoard &board)
  : mArr(new piece_t[64])
{
  assert(board.mArr != nullptr);
  std::copy(board.begin(), board.end(), begin());
}

//
// Move ctor.
//
inline
BasicBoard::BasicBoard(BasicBoard &&board) noexcept
  : mArr(board.mArr)
{
  assert(mArr != nullptr);
  board.mArr = nullptr;
}

//
// Copy Assignment.
//
inline BasicBoard&
BasicBoard::operator=(const BasicBoard &board) noexcept
{
  assert(mArr != nullptr);
  assert(board.mArr != nullptr);
  std::copy(board.begin(), board.end(), begin());
  return *this;
}

//
// Move assignment.
//
inline BasicBoard&
BasicBoard::operator=(BasicBoard &&board) noexcept
{
  assert(mArr != nullptr);
  assert(board.mArr != nullptr);
  std::swap(mArr, board.mArr);
  return *this;
}

//
// Dtor.
//
inline
BasicBoard::~BasicBoard() noexcept
{
  if (mArr != nullptr)
    delete[] mArr;
}

//
// Blank board ctor.
//
inline
BasicBoard::BasicBoard(InitEmpty)
  : mArr(new piece_t[SIZE]()) {}

//
// get the piece from a given square
//
inline piece_t
BasicBoard::get(dim_t row, dim_t column) const noexcept
{
  assert(mArr != nullptr);
  assert(inBoard(row, column));
  return mArr[index(row, column)];
}

//
// clear the contents of a square
//
inline void
BasicBoard::clear(dim_t row, dim_t column) noexcept
{
  assert(mArr != nullptr);
  assert(inBoard(row, column));
  mArr[index(row, column)] = 0;
}

//
// put a piece on a square
//
inline void
BasicBoard::put(dim_t row, dim_t column, piece_t piece) noexcept
{
  assert(mArr != nullptr);
  assert(inBoard(row, column));
  mArr[index(row, column)] = piece;
}

//
// put a piece on a square
//
inline void
BasicBoard::put(dim_t row, dim_t column, Piece piece, Color color) noexcept
{
  assert(mArr != nullptr);
  assert(inBoard(row, column));
  mArr[index(row, column)] = color | piece;
}

//
// return the begin iterator
//
inline BasicBoard::iterator
BasicBoard::begin() const noexcept
{
  assert(mArr != nullptr);
  return mArr;
}

//
// return the end iterator
//
inline BasicBoard::iterator
BasicBoard::end() const noexcept
{
  assert(mArr != nullptr);
  return mArr + SIZE;
}

//
// return the read only begin iterator
//
inline BasicBoard::const_iterator
BasicBoard::cbegin() const noexcept
{
  assert(mArr != nullptr);
  return mArr;
}

//
// return the read only end iterator
//
inline BasicBoard::const_iterator
BasicBoard::cend() const noexcept
{
  assert(mArr != nullptr);
  return mArr + SIZE;
}

//
// create an empty board
//
inline BasicBoard
BasicBoard::emptyBoard()
{
  return BasicBoard(InitEmpty::INIT);
}

//
// check row and column are in board
//
inline bool
BasicBoard::inBoard(dim_t row, dim_t column) noexcept
{
  return row >= 0 && row < DIM && column >= 0 && column < DIM;
}

//
// equality operator
//
inline bool
operator==(const BasicBoard &board1, const BasicBoard &board2) noexcept
{
  return std::equal(board1.begin(), board1.end(), board2.begin());
}

//
// non-equality operator
//
inline bool
operator!=(const BasicBoard &board1, const BasicBoard &board2) noexcept
{
  return !(board1 == board2);
}

} // zoor
#endif // _BASICBOARD_H
