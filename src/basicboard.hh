/////////////////////////////////////////////////////////////////////////////////////
/// @file basicboard.hh
/// @author Omar A Serrano
/// @date 2016-04-28
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICBOARD_H
#define _BASICBOARD_H

//
// STL
//
#include <iterator>

//
// zoor
//
#include "basictypes.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// BoardIter
/////////////////////////////////////////////////////////////////////////////////////

class BoardIter
  : public std::iterator<std::random_iterator_tag, piece_t>
{
public:
  // don't permit default construction
  BoardIter() = delete;

  ///
  /// @brief Initialize with pointer to piece.
  /// @param piece A pointer to a piece on a board.
  /// @throw Never throws.
  ///
  BoardIter(piece_t *piece) noexcept;

  ///
  /// @brief Default copy ctor.
  /// @param iter The @c BoardIter to be copied.
  /// @throw Never throws.
  ///
  BoardIter(const BoardIter &iter) noexcept = default;

  ///
  /// @brief Default move ctor.
  /// @param iter The @c BoardIter to be moved.
  /// @throw Never throws.
  ///
  BoardIter(BoardIter &&iter) noexcept = default;

  ///
  /// @brief Default copy assignment.
  /// @param iter The @c BoardIter to be copied.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator=(const BoardIter &iter) noexcept = default;

  ///
  /// @brief Default move assignment.
  /// @param iter The @c BoardIter to be moved.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator=(BoardIter &&iter) noexcept = default;

  ///
  /// @brief Default dtor.
  /// @throw Never throws.
  ///
  ~BoardIter() noexcept = default;

  ///
  /// @brief Prefix increment.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator++() noexcept;

  ///
  /// @brief Postfix increment.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter
  operator++(int) noexcept;

  ///
  /// @brief Prefix decrement.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator--() noexcept;

  ///
  /// @brief Postfix decrement.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter
  operator--(int) noexcept;

  ///
  /// @brief Addition assignment.
  /// @param value The value added to the iterator.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator+=(difference_type value) noexcept;

  ///
  /// @brief Subtraction assignment.
  /// @param value The value subtracted to the iterator.
  /// @return A reference to itself.
  /// @throw Never throws.
  ///
  BoardIter&
  operator-=(difference_type value) noexcept;

  ///
  /// @brief Get a reference to piece.
  /// @return Const reference to piece.
  /// @throw Never throws.
  ///
  const reference
  operator*() const noexcept;

private:
  // pointer to read-only piece
  const piece_t *mIter;
};

///
/// @brief Increment the iterator by a given value.
/// @param iter The @c BoardIter.
/// @param value The value to increment iter.
/// @return A copy of iter incremented by value.
/// @throw Never throws.
///
BoardIter
operator+(const BoardIter &iter, BoardIter::difference_type value) noexcept;

///
/// @brief Decrement the iterator by a given value.
/// @param iter The @c BoardIter.
/// @param value The value to decrement iter.
/// @return A copy of iter decremented by value.
/// @throw Never throws.
///
BoardIter
operator-(const BoardIter &iter, BoardIter::difference_type value) noexcept;

/////////////////////////////////////////////////////////////////////////////////////
// BasicBoard
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief A simple board that represents the position in a chess board.
///
class BasicBoard:
{
public:
  ///
  /// @brief The number of squares in the @c SimpleBoard.
  ///
  static constexpr size_t SIZE = 64;

  ///
  /// @brief Default ctor.
  /// @details Initializes the board with the normal setup for beginning game.
  /// @throw May throw bad memory allocation.
  ///
  BasicBoard();

  ///
  /// @brief Copy ctor.
  /// @param board The @c SimpleBoard to be copied.
  /// @throw May throw bad memory allocation.
  ///
  BasicBoard(const BasicBoard &board);

  ///
  /// @brief Move ctor.
  /// @param board The @c SimpleBoard being moved.
  /// @throw Never throws.
  ///
  BasicBoard(BasicBoard &&board) noexcept;

  ///
  /// @brief Copy assignment.
  /// @param board The @c SimpleBoard being assigned.
  /// @return A reference to @c BasicBoard.
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(const BasicBoard &board) noexcept;

  ///
  /// @brief Move assignment.
  /// @param board The @c SimpleBoard being moved.
  /// @return A reference to @c BasicBoard.
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(BasicBoard &&board) noexcept;

  ///
  /// @brief Dtor.
  /// @throw Never throws.
  ///
  ~BasicBoard() noexcept;

  ///
  /// @brief Obtain the contents of a given square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @return The piece located at the given square.
  /// @throw Never throws.
  ///
  piece_t
  get(dim_t row, dim_t column) const noexcept;

  ///
  /// @brief Put a chess piece on a square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @param piece The type of chess piece.
  /// @throw Never throws.
  ///
  void
  put(dim_t row, dim_t column, piece_t piece) noexcept;

  ///
  /// @brief Put a chess piece on a square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @param piece The type of chess piece.
  /// @param color The color of the chess piece.
  /// @throw Never throws.
  ///
  void
  put(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @brief Get iterator to the first square on the board.
  /// @throw Never throws.
  ///
  iterator
  begin() const noexcept;

  ///
  /// @brief Get iterator to one past the last square.
  /// @throw Never throws.
  ///
  iterator
  end() const noexcept;

private:
  // pointer to the array
  piece_t *mArr;
};

} // zoor
#endif // _BASICBOARD_H
