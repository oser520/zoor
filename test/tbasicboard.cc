/////////////////////////////////////////////////////////////////////////////////////
/// @file tbasicboard.cc
/// @author Omar A Serrano
/// @date 2016-05-03
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <sstream>

//
// zoor
//
#include "basictypes.hh"
#include "basicboard.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//

//
// access all of zoor
//
using zoor::BasicBoard;
using zoor::Piece;
using zoor::Color;

//
// test default ctor and get()
//
TEST(BasicBoard, DefaultCtorAndGet)
{
  BasicBoard board;

  EXPECT_EQ(board.get(0,0), Color::W|Piece::R);
  EXPECT_EQ(board.get(0,1), Color::W|Piece::N);
  EXPECT_EQ(board.get(0,2), Color::W|Piece::B);
  EXPECT_EQ(board.get(0,3), Color::W|Piece::Q);
  EXPECT_EQ(board.get(0,4), Color::W|Piece::K);
  EXPECT_EQ(board.get(0,5), Color::W|Piece::B);
  EXPECT_EQ(board.get(0,6), Color::W|Piece::N);
  EXPECT_EQ(board.get(0,7), Color::W|Piece::R);

  for (int i = 0; i < BasicBoard::DIM; ++i) {
    // white pawns
    EXPECT_EQ(board.get(1,i), Color::W|Piece::P);

    // black pawns
    EXPECT_EQ(board.get(6,i), Color::B|Piece::P);
  }

  // test empty squares
  for (int i = 2; i < BasicBoard::DIM-2; ++i) {
    for (int j = 0; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(board.get(i, j), 0);
  }
}

//
// test clear
//
TEST(BasicBoard, Clear)
{
  BasicBoard board;

  // test non-empty squares
  for (int i = 0; i < BasicBoard::DIM; ++i) {
    board.clear(0, i);
    EXPECT_EQ(board.get(0, i), 0);
  }

  // test empty squares
  for (int i = 0; i < BasicBoard::DIM; ++i) {
    board.clear(2, i);
    EXPECT_EQ(board.get(2, i), 0);
  }
}

//
// copy ctor
//
TEST(BasicBoard, CopyCtor)
{
  BasicBoard board1;
  BasicBoard board2(board1);

  EXPECT_EQ(board1, board2);
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

