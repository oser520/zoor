/////////////////////////////////////////////////////////////////////////////////////
//! @file tbasicboard.cc
//! @author Omar A Serrano
//! @date 2016-05-03
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <utility>

//
// zoor
//
#include "basictypes.hh"
#include "basicboard.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace zoor {

//
// using from STL
//
using std::pair;
using std::move;

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
// test emptyBoard() constructor
//
TEST(BasicBoard, EmptyBoard)
{
  auto board = BasicBoard::emptyBoard();
  for (auto &p : board)
    EXPECT_EQ(0, p);
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
// test put
//
TEST(BasicBoard, Put)
{
  BasicBoard board;

  board.put(0, 0, Color::NONE|Piece::NONE);
  EXPECT_EQ(board.get(0, 0), 0);

  board.put(0, 1, Piece::NONE, Color::NONE);
  EXPECT_EQ(board.get(0, 1), 0);

  pair<Piece, Color> pArr[] = {
    {Piece::P, Color::W},
    {Piece::N, Color::W},
    {Piece::B, Color::W},
    {Piece::R, Color::W},
    {Piece::Q, Color::W},
    {Piece::K, Color::W},
  };

  // put white pieces
  for (int i = 0; i < 5; ++i) {
    board.put(2, i, pArr[i].first, pArr[i].second);
    board.put(3, i, pArr[i].second | pArr[i].first);
    EXPECT_EQ(board.get(2, i), board.get(3,i));
    EXPECT_NE(board.get(2, i), 0);
  }

  // change color to black
  for (int i = 0; i < 5; ++i)
    pArr[i].second = Color::B;

  // put black pieces
  for (int i = 0; i < 5; ++i) {
    board.put(4, i, pArr[i].first, pArr[i].second);
    board.put(5, i, pArr[i].second | pArr[i].first);
    EXPECT_EQ(board.get(4, i), board.get(5,i));
    EXPECT_NE(board.get(4, i), 0);

    // compare against white pieces
    EXPECT_NE(board.get(4, i), board.get(3,i));
  }
}

//
// test iterators
//
TEST(BasicBoard, Iterator)
{
  BasicBoard board;

  auto it = board.begin();

  for (int i = 0; i < BasicBoard::DIM; ++i) {
    for (int j = 0; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(*it++, board.get(i, j));
  }

  // the last piece is a black rook
  it = const_cast<decltype(it)>(board.cend() - 1);
  EXPECT_EQ(*it, board.get(7,7));
  EXPECT_EQ(getPiece(*it), Piece::R);
  EXPECT_EQ(getColor(*it), Color::B);

  auto itc = board.cbegin();
  auto ite = board.cend();
  int i = 0;

  while (itc != ite) {
    ++itc;
    ++i;
  }

  EXPECT_EQ(i, BasicBoard::SIZE);
}

//
// copy ctor
//
TEST(BasicBoard, CopyCtor)
{
  BasicBoard board1;
  board1.put(0, 0, 0);
  BasicBoard board2(board1);
  EXPECT_EQ(board2.get(0, 0), 0);
  EXPECT_EQ(board1, board2);
}

//
// move ctor
//
TEST(BasicBoard, MoveCtor)
{
  BasicBoard board1;
  board1.put(0, 0, 0);
  BasicBoard board2(move(board1));
  EXPECT_EQ(board2.get(0, 0), 0);
}

//
// copy assignment
//
TEST(BasicBoard, CopyAssign)
{
  BasicBoard board1, board2;

  board1.put(0, 0, 0);
  board2.put(0, 1, 0);
  EXPECT_EQ(board1.get(0, 0), 0);
  EXPECT_EQ(board2.get(0, 1), 0);

  board2 = board1;
  EXPECT_EQ(board2.get(0, 0), 0);
  EXPECT_NE(board2.get(0, 1), 0);
}

//
// move assignment
//
TEST(BasicBoard, MoveAssign)
{
  BasicBoard board1, board2;

  board1.put(0, 0, 0);
  board2.put(0, 1, 0);
  EXPECT_EQ(board1.get(0, 0), 0);
  EXPECT_EQ(board2.get(0, 1), 0);

  board2 = move(board1);
  EXPECT_EQ(board1.get(0, 1), 0);
  EXPECT_NE(board1.get(0, 0), 0);
  EXPECT_EQ(board2.get(0, 0), 0);
  EXPECT_NE(board2.get(0, 1), 0);
}

//
// test equality operator
//
TEST(BasicBoard, EqualOp)
{
  BasicBoard board1, board2;

  EXPECT_EQ(board1, board2);
  board1.clear(0, 0);
  EXPECT_NE(board1, board2);
}

} // namespace zoor
