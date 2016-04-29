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

  BasicBoard();
  BasicBoard(const BasicBoard &board) noexcept;
  BasicBoard(BasicBoard &&board) noexcept;
  BasicBoard&
  operator=(const BasicBoard &board);

private:
  // pointer to the array
  piececode_t *mArr;
};

} // zoor
#endif // _BASICBOARD_H
