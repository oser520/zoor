/**
 * @file board.cc
 * @author Omar A Serrano
 * @date 2015-12-26
 */

// STL headers
#include <vector>
#include <iostream>
#include <algorithm>

// zoor headers
#include "board.hh"

namespace zoor {

/**
 * TODO: determine how to initialize default board.
 */
Board::Board() {}

/**
 * TODO: implement getBoardsFromMoves function
 */
vector<Board> Board::getBoardsFromMoves() const noexcept
{
  return vector<Board>();
}

/**
 * TODO: implement output operator for Board
 */
std:ostream& operator<<(std:ostream &os, const Board &board)
{
  return os;
}

bool operator==(const Board &boar1, const Board &board2) noexcept
{
  return board1.mColorMove == board2.mColorMove
      && std::equal(board1.begin(), board1.end(), board2.begin());
}

bool operator!=(const Board &boar1, const Board &board2) noexcept
{
  return !(board1 == board2);
}

} // namespace zoor
