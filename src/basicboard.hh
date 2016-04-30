/////////////////////////////////////////////////////////////////////////////////////
/// @file basicboard.hh
/// @author Omar A Serrano
/// @date 2016-04-28
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICBOARD_H
#define _BASICBOARD_H

//
// zoor
//
#include "piececode.hh"

namespace zoor {

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
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(const BasicBoard &board) noexcept;

  ///
  /// @brief Move assignment.
  /// @param board The @c SimpleBoard being moved.
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(BasicBoard &&board) noexcept;

  ///
  /// @brief Dtor.
  /// @throw Never throws.
  ///
  ~BasicBoard() noexcept;

private:
  // pointer to the array
  piececode_t *mArr;
};

} // zoor
#endif // _BASICBOARD_H
