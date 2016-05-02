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

//
// zoor
//
#include "basicboard.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// BasicBoard
/////////////////////////////////////////////////////////////////////////////////////

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
} // zoor
