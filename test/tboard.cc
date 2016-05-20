/////////////////////////////////////////////////////////////////////////////////////
/// @file tboard.cc
/// @author Omar A Serrano
/// @date 2016-03-19
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "fenrecord.hh"
#include "iofen.hh"
#include "piecemove.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// from STL
//
using std::ostringstream;
using std::pair;
using std::vector;

//
// from zoor
//
using namespace zoor;

//
// test Board default ctor
//
TEST(Board, DefaultCtor)
{
  Board board;
  EXPECT_FALSE(board.canCastle());
  EXPECT_FALSE(board.canCastleLong());
  EXPECT_EQ(Color::W, board.nextTurn());

  auto pm = board.lastMove();
  EXPECT_EQ(0, pm.sRow());
  EXPECT_EQ(0, pm.sColumn());
  EXPECT_EQ(0, pm.sCode());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());
  EXPECT_EQ(0, pm.dCode());
  EXPECT_EQ(0, pm.xRow());
  EXPECT_EQ(0, pm.xColumn());
  EXPECT_EQ(0, pm.xCode());

  auto sq = board(0, 0);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
  EXPECT_EQ(Piece::R, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(6, 2);
  EXPECT_EQ(6, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::P, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(7, 2);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::B, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 3);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(3, sq.column());
  EXPECT_EQ(Piece::Q, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(7, 4);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(4, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 5);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(Piece::B, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(7, 6);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(6, sq.column());
  EXPECT_EQ(Piece::N, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 7);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(7, sq.column());
  EXPECT_EQ(Piece::R, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(4, 5);
  EXPECT_EQ(4, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(Piece::NONE, sq.piece());
  EXPECT_EQ(Color::NONE, sq.color());
}

//
// test ctor with 4 param
//
TEST(Board, CtorWithVectorColorInfoMoveParam)
{
  vector<Square> sqList;
  sqList.emplace_back(0, 0, Piece::K, Color::W);
  sqList.emplace_back(0, 2, Piece::K, Color::B);

  BoardInfo info;
  info.rookA1On().rookA8On().rookH1On().rookH8On();

  PieceMove pm(0, 3, Color::B|Piece::K, 0, 2);

  Board board(sqList, Color::W, info, pm);

  EXPECT_EQ(Color::W, board.nextTurn());
  EXPECT_EQ(pm, board.lastMove());
  EXPECT_FALSE(board.canCastle());
  EXPECT_FALSE(board.canCastleLong());

  auto sq = board(0, 0);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(0, 1);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(1, sq.column());
  EXPECT_EQ(0, sq.code());

  sq = board(0, 2);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  // check other squares in first row are empty
  for (int i = 3; i < BasicBoard::DIM; ++i)
    EXPECT_EQ(0, board(0, i).code());

  // check other squares in board are empty
  for (int i = 1; i < BasicBoard::DIM; ++i) {
    for (int j = 1; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(0, board(i, j).code());
  }
}

//
// test canCastle and canCastleLong for white
//
TEST(Board, CanWhiteCastle)
{
  vector<FenRecord> fenList = readFen("fen/canWhiteCastle.fen");

  // first bool is expected for canCastle()
  // second bool is expected for canCastleLong()
  vector<pair<bool, bool>> boolList = {
    {true, true},   // k7/8/8/8/4n3/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/4n3/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/4n3/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/8/7n/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/6n1/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/8/8/8/n7/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/8/8/b7/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/4b3/8/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/4b3/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/7b/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/b7/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/4r3/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/5r2/8/8/8/8/8/R3K2R w KQ - 0 40
    {true, true},   // k7/7r/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/2r3r1/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/7q/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/7q/8/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/7q/8/8/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/7q/8/8/8/8/R3K2R w KQ - 0 40
    {true, true},   // k7/7q/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/4q3/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/8/Rq2K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/8/7p/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/8/7p/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/4p3/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/8/8/8/2p5/R3K2R w KQ - 0 40
    {true, false},  // 8/8/8/8/8/8/1k6/R3K2R w KQ - 0 40
    {false, true},  // 8/8/8/8/8/8/6k1/R3K2R w KQ - 0 40
    {true, true}    // 8/8/8/8/8/6k1/8/R3K2R w KQ - 0 40
  };

  // make sure we don't omit any tests
  EXPECT_EQ(fenList.size(), boolList.size());

  auto fenIt = fenList.cbegin();
  for (const auto &bools : boolList) {
    auto pb = fenIt->boardPtr();
    EXPECT_EQ(bools.first, pb->canCastle());
    EXPECT_EQ(bools.second, pb->canCastleLong());
    ++fenIt;
  }
}

//
// test canCaslte and canCastleLong for black
//
TEST(Board, CanBlackCastle)
{
  vector<FenRecord> fenList = readFen("fen/canBlackCastle.fen");

  // first bool is expected for canCastle()
  // second bool is expected for canCastleLong()
  vector<pair<bool, bool>> boolList = {
    {true, true},   // r3k2r/8/8/4N3/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/4N3/8/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/4N3/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/7N/8/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/8/6N1/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/N7/8/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/B7/8/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/4B3/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/4B3/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/8/7B/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/B7/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/4R3/7K b kq - 0 40
    {false, true},  // r3k2r/8/8/8/8/8/5R2/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/8/8/8/7R/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/2R3R1/7K b kq - 0 40
    {false, true},  // r3k2r/8/7Q/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/7Q/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/8/8/8/7Q/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/8/8/8/8/7Q/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/8/8/8/7Q/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/4Q3/7K b kq - 0 40
    {false, false}, // rQ2k2r/8/8/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/7P/8/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/7P/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/4P3/8/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/2P5/8/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/1K6/8/8/8/8/8/8 b kq - 0 40
    {false, true},  // r3k2r/6K1/8/8/8/8/8/8 b kq - 0 40
    {true, true}    // r3k2r/8/6K1/8/8/8/8/8 b kq - 0 40
  };

  // make sure we don't omit any tests
  EXPECT_EQ(fenList.size(), boolList.size());

  auto fenIt = fenList.cbegin();
  for (const auto &bools : boolList) {
    auto pb = fenIt->boardPtr();
    EXPECT_EQ(bools.first, pb->canCastle());
    EXPECT_EQ(bools.second, pb->canCastleLong());
    ++fenIt;
  }
}

//
// test getMoves with row and column specified
//
TEST(Board, DISABLED_GetMovesRowCol)
{
  // TODO
}

//
// test getMoves for all moves on the board
//
TEST(Board, DISABLED_GetMoves)
{
  // TODO
}

//
// test getBoards
//
TEST(Board, DISABLED_GetBoards)
{
  // TODO
}

//
// test makeMoveCopy
//
TEST(Board, DISABLED_MakeMoveCopy)
{
  // TODO
}

//
// test makeMove
//
TEST(Board, DISABLED_MakeMove)
{
  // TODO
}

//
// test lastMove
//
TEST(Board, DISABLED_LastMove)
{
  // TODO
}

//
// test iterators
//
TEST(Board, Iterators)
{
  Board board;
  auto it = board.begin();

  EXPECT_EQ(Color::W|Piece::R, *it);
  EXPECT_EQ(Color::W|Piece::N, *(it+6));
  EXPECT_EQ(Color::W|Piece::R, *(it+7));

  for (int i = 0; i < BasicBoard::DIM; ++i) {
    for (int j = 0; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(board(i, j).code(), *it++);
  }

  EXPECT_EQ(board.end(), it);
}

//
// test jump
//
TEST(Board, DISABLED_Jump)
{
  // TODO
}

//
// test isCheckPawn on white king
//
TEST(Board, WhiteOnCheckFromPawn)
{
  auto fenList = readFen("fen/whiteOnCheckFromPawn.fen");

  // FEN 1: k7/8/8/8/8/2p5/3K4/8 w - - 0 1
  // FEN 2: k7/8/8/8/8/4p3/3K4/8 w - - 0 1
  EXPECT_TRUE(fenList[0].boardPtr()->isCheckPawn(1, 3));
  EXPECT_TRUE(fenList[1].boardPtr()->isCheckPawn(1, 3));

  // FEN 3: k7/8/8/8/8/3p4/3K4/8 w - - 0 1
  // FEN 4: k7/8/8/8/8/8/2pK4/8 w - - 0 1
  // FEN 5: k7/8/8/8/8/8/3Kp3/8 w - - 0 1
  for (auto it = fenList.cbegin()+2; it != fenList.cend(); ++it)
    EXPECT_FALSE(it->boardPtr()->isCheckPawn(1, 3));
}

//
// test isCheckPawn on black king
//
TEST(Board, BlackOnCheckFromPawn)
{
  auto fenList = readFen("fen/blackOnCheckFromPawn.fen");

  // FEN 1: 8/3k4/2P5/8/8/8/8/K7 b - - 0 1
  // FEN 2: 8/3k4/4P3/8/8/8/8/K7 b - - 0 1
  EXPECT_TRUE(fenList[0].boardPtr()->isCheckPawn(6, 3));
  EXPECT_TRUE(fenList[1].boardPtr()->isCheckPawn(6, 3));

  // FEN 3: 8/3k4/3P4/8/8/8/8/K7 b - - 0 1
  // FEN 4: 8/2Pk4/8/8/8/8/8/K7 b - - 0 1
  // FEN 5: 8/3kP3/8/8/8/8/8/K7 b - - 0 1
  for (auto it = fenList.cbegin()+2; it != fenList.cend(); ++it)
    EXPECT_FALSE(it->boardPtr()->isCheckPawn(6, 3));
}

//
// test isCheckKnight on white's turn
//
TEST(Board, WhiteOnCheckFromKnight)
{
  vector<bool> boolList = {
    true,  // FEN 1: k7/8/4n3/8/3K4/8/8/8 w - - 0 1
    true,  // FEN 2: k7/8/8/5n2/3K4/8/8/8 w - - 0 1
    true,  // FEN 3: k7/8/8/8/3K4/5n2/8/8 w - - 0 1
    true,  // FEN 4: k7/8/8/8/3K4/8/4n3/8 w - - 0 1
    true,  // FEN 5: k7/8/8/8/3K4/8/2n5/8 w - - 0 1
    true,  // FEN 6: k7/8/8/8/3K4/1n6/8/8 w - - 0 1
    true,  // FEN 7: k7/8/8/1n6/3K4/8/8/8 w - - 0 1
    true,  // FEN 8: k7/8/2n5/8/3K4/8/8/8 w - - 0 1
    false, // FEN 9: k7/8/3n4/3n4/3K4/3n4/3n4/8 w - - 0 1
    false, // FEN 10: k7/8/8/2n5/2nK4/2n5/8/8 w - - 0 1
    false  // FEN 11: k7/8/8/4n3/3Kn3/4n3/8/8 w - - 0 1
  };

  auto fenList = readFen("fen/whiteOnCheckFromKnight.fen");

  EXPECT_EQ(boolList.size(), fenList.size());

  auto itfen = fenList.cbegin();
  auto itbool = boolList.cbegin();
  auto ite = fenList.cend();

  while (itfen != ite) {
    EXPECT_EQ(*itbool, itfen->boardPtr()->isCheckKnight(3, 3));
    ++itbool;
    ++itfen;
  }
}

//
// test isCheckKnight on blacks's turn
//
TEST(Board, BlackOnCheckFromKnight)
{
  vector<bool> boolList = {
    true,  // FEN 1: K7/8/4N3/8/3k4/8/8/8 b - - 0 1
    true,  // FEN 2: K7/8/8/5N2/3k4/8/8/8 b - - 0 1
    true,  // FEN 3: K7/8/8/8/3k4/5N2/8/8 b - - 0 1
    true,  // FEN 4: K7/8/8/8/3k4/8/4N3/8 b - - 0 1
    true,  // FEN 5: K7/8/8/8/3k4/8/2N5/8 b - - 0 1
    true,  // FEN 6: K7/8/8/8/3k4/1N6/8/8 b - - 0 1
    true,  // FEN 7: K7/8/8/1N6/3k4/8/8/8 b - - 0 1
    true,  // FEN 8: K7/8/2N5/8/3k4/8/8/8 b - - 0 1
    false, // FEN 9: K7/8/3N4/3N4/3k4/3N4/3N4/8 b - - 0 1
    false, // FEN 10: K7/8/8/2N5/2Nk4/2N5/8/8 b - - 0 1
    false  // FEN 11: K7/8/8/4N3/3kN3/4N3/8/8 b - - 0 1
  };

  auto fenList = readFen("fen/blackOnCheckFromKnight.fen");

  EXPECT_EQ(boolList.size(), fenList.size());

  auto itfen = fenList.cbegin();
  auto itbool = boolList.cbegin();
  auto ite = fenList.cend();

  while (itfen != ite) {
    EXPECT_EQ(*itbool, itfen->boardPtr()->isCheckKnight(3, 3));
    ++itbool;
    ++itfen;
  }
}

//
// test isCheckBishop on white's turn
//
TEST(Board, WhiteOnCheckFromBishop)
{
  auto fenList = readFen("fen/whiteOnCheckFromBishop.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+4;
  auto itend = fenList.cend();

  // FEN 1: k7/8/5b2/8/3K4/8/8/8 w - - 0 1
  // FEN 2: k7/8/1b6/8/3K4/8/8/8 w - - 0 1
  // FEN 3: k7/8/8/8/3K4/8/5b2/8 w - - 0 1
  // FEN 4: k7/8/8/8/3K4/8/1b6/8 w - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckBishop(3, 3));

  // FEN 5: k7/8/7b/8/3K4/8/8/8 w - - 0 1
  // FEN 6: k7/8/6b1/8/3K4/8/8/8 w - - 0 1
  // FEN 7: k7/8/4b3/8/3K4/8/8/8 w - - 0 1
  // FEN 8: k7/8/3b4/8/3K4/8/8/8 w - - 0 1
  // FEN 9: k7/8/2b5/8/3K4/8/8/8 w - - 0 1
  // FEN 10: k7/8/b7/8/3K4/8/8/8 w - - 0 1
  // FEN 11: k7/8/8/8/3K4/8/7b/8 w - - 0 1
  // FEN 12: k7/8/8/8/3K4/8/6b1/8 w - - 0 1
  // FEN 13: k7/8/8/8/3K4/8/4b3/8 w - - 0 1
  // FEN 14: k7/8/8/8/3K4/8/3b4/8 w - - 0 1
  // FEN 15: k7/8/8/8/3K4/8/2b5/8 w - - 0 1
  // FEN 16: k7/8/8/8/3K4/8/b7/8 w - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckBishop(3, 3));
}

//
// test isCheckBishop on blacks's turn
//
TEST(Board, BlackOnCheckFromBishop)
{
  auto fenList = readFen("fen/blackOnCheckFromBishop.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+4;
  auto itend = fenList.cend();

  // FEN 1: K7/8/5B2/8/3k4/8/8/8 b - - 0 1
  // FEN 2: K7/8/1B6/8/3k4/8/8/8 b - - 0 1
  // FEN 3: K7/8/8/8/3k4/8/5B2/8 b - - 0 1
  // FEN 4: K7/8/8/8/3k4/8/1B6/8 b - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckBishop(3, 3));

  // FEN 5: K7/8/7B/8/3k4/8/8/8 b - - 0 1
  // FEN 6: K7/8/6B1/8/3k4/8/8/8 b - - 0 1
  // FEN 7: K7/8/4B3/8/3k4/8/8/8 b - - 0 1
  // FEN 8: K7/8/3B4/8/3k4/8/8/8 b - - 0 1
  // FEN 9: K7/8/2B5/8/3k4/8/8/8 b - - 0 1
  // FEN 10: K7/8/B7/8/3k4/8/8/8 b - - 0 1
  // FEN 11: K7/8/8/8/3k4/8/7B/8 b - - 0 1
  // FEN 12: K7/8/8/8/3k4/8/6B1/8 b - - 0 1
  // FEN 13: K7/8/8/8/3k4/8/4B3/8 b - - 0 1
  // FEN 14: K7/8/8/8/3k4/8/3B4/8 b - - 0 1
  // FEN 15: K7/8/8/8/3k4/8/2B5/8 b - - 0 1
  // FEN 16: K7/8/8/8/3k4/8/B7/8 b - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckBishop(3, 3));
}

//
// test isCheckRook on white's turn
//
TEST(Board, WhiteOnCheckFromRook)
{
  auto fenList = readFen("fen/whiteOnCheckFromRook.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+4;
  auto itend = fenList.cend();

  // FEN 1: k7/8/8/8/3K3r/8/8/8 w - - 0 1
  // FEN 2: k7/3r4/8/8/3K4/8/8/8 w - - 0 1
  // FEN 3: k7/8/8/8/r2K4/8/8/8 w - - 0 1
  // FEN 4: k7/8/8/8/3K4/8/8/3r4 w - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckRook(3, 3));

  // FEN 5: k7/6r1/8/8/3K4/8/8/8 w - - 0 1
  // FEN 6: k7/5r2/8/8/3K4/8/8/8 w - - 0 1
  // FEN 7: k7/4r3/8/8/3K4/8/8/8 w - - 0 1
  // FEN 8: k7/8/8/8/3K4/8/8/2r5 w - - 0 1
  // FEN 9: k7/8/8/8/3K4/8/8/1r6 w - - 0 1
  // FEN 10: k7/8/8/8/3K4/8/8/r7 w - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckRook(3, 3));
}

//
// test isCheckRook on black's turn
//
TEST(Board, BlackOnCheckFromRook)
{
  auto fenList = readFen("fen/blackOnCheckFromRook.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+4;
  auto itend = fenList.cend();

  // FEN 1: K7/8/8/8/3k3R/8/8/8 b - - 0 1
  // FEN 2: K7/3R4/8/8/3k4/8/8/8 b - - 0 1
  // FEN 3: K7/8/8/8/R2k4/8/8/8 b - - 0 1
  // FEN 4: K7/8/8/8/3k4/8/8/3R4 b - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckRook(3, 3));

  // FEN 5: K7/6R1/8/8/3k4/8/8/8 b - - 0 1
  // FEN 6: K7/5R2/8/8/3k4/8/8/8 b - - 0 1
  // FEN 7: K7/4R3/8/8/3k4/8/8/8 b - - 0 1
  // FEN 8: K7/8/8/8/3k4/8/8/2R5 b - - 0 1
  // FEN 9: K7/8/8/8/3k4/8/8/1R6 b - - 0 1
  // FEN 10: K7/8/8/8/3k4/8/8/R7 b - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckRook(3, 3));
}

//
// test isCheckQueen on white's turn to move
//
TEST(Board, WhiteOnCheckFromQueen)
{
  auto fenList = readFen("fen/whiteOnCheckFromQueen.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+8;
  auto itend = fenList.cend();

  // FEN 1: k7/8/8/8/3K3q/8/8/8 w - - 0 1
  // FEN 2: k7/3q4/8/8/3K4/8/8/8 w - - 0 1
  // FEN 3: k7/8/8/8/q2K4/8/8/8 w - - 0 1
  // FEN 4: k7/8/8/8/3K4/8/8/3q4 w - - 0 1
  // FEN 5: k7/6q1/8/8/3K4/8/8/8 w - - 0 1
  // FEN 6: k7/8/8/8/3K4/8/8/q7 w - - 0 1
  // FEN 7: k7/8/8/8/3K4/8/8/6q1 w - - 0 1
  // FEN 8: k7/q7/8/8/3K4/8/8/8 w - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckQueen(3, 3));

  // FEN 9: k7/5q2/8/8/3K4/8/8/8 w - - 0 1
  // FEN 10: k7/4q3/8/8/3K4/8/8/8 w - - 0 1
  // FEN 11: k7/8/8/8/3K4/8/8/2q5 w - - 0 1
  // FEN 12: k7/8/8/8/3K4/8/8/1q6 w - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckQueen(3, 3));
}

//
// test isCheckQueen on black's turn to move
//
TEST(Board, BlackOnCheckFromQueen)
{
  auto fenList = readFen("fen/blackOnCheckFromQueen.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+8;
  auto itend = fenList.cend();

  // FEN 1: K7/8/8/8/3k3Q/8/8/8 b - - 0 1
  // FEN 2: K7/3Q4/8/8/3k4/8/8/8 b - - 0 1
  // FEN 3: K7/8/8/8/Q2k4/8/8/8 b - - 0 1
  // FEN 4: K7/8/8/8/3k4/8/8/3Q4 b - - 0 1
  // FEN 5: K7/6Q1/8/8/3k4/8/8/8 b - - 0 1
  // FEN 6: K7/8/8/8/3k4/8/8/Q7 b - - 0 1
  // FEN 7: K7/8/8/8/3k4/8/8/6Q1 b - - 0 1
  // FEN 8: K7/Q7/8/8/3k4/8/8/8 b - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckQueen(3, 3));

  // FEN 9: K7/5Q2/8/8/3k4/8/8/8 b - - 0 1
  // FEN 10: K7/4Q3/8/8/3k4/8/8/8 b - - 0 1
  // FEN 11: K7/8/8/8/3k4/8/8/2Q5 b - - 0 1
  // FEN 12: K7/8/8/8/3k4/8/8/1Q6 b - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckQueen(3, 3));
}

//
// test isCheckKing on white's turn to move
//
TEST(Board, WhiteOnCheckFromKing)
{
  auto fenList = readFen("fen/whiteOnCheckFromKing.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+8;
  auto itend = fenList.cend();

  // FEN 1: 8/8/8/4k3/3K4/8/8/8 w - - 0 1
  // FEN 2: 8/8/8/3k4/3K4/8/8/8 w - - 0 1
  // FEN 3: 8/8/8/2k5/3K4/8/8/8 w - - 0 1
  // FEN 4: 8/8/8/8/2kK4/8/8/8 w - - 0 1
  // FEN 5: 8/8/8/8/3Kk3/8/8/8 w - - 0 1
  // FEN 6: 8/8/8/8/3K4/4k3/8/8 w - - 0 1
  // FEN 7: 8/8/8/8/3K4/3k4/8/8 w - - 0 1
  // FEN 8: 8/8/8/8/3K4/2k5/8/8 w - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckKing(3, 3));

  // FEN 9: 8/8/8/5k2/3K4/8/8/8 w - - 0 1
  // FEN 10: 8/8/8/1k6/3K4/8/8/8 w - - 0 1
  // FEN 11: 8/8/8/8/1k1K4/8/8/8 w - - 0 1
  // FEN 12: 8/8/8/8/3K1k2/8/8/8 w - - 0 1
  // FEN 13: 8/8/8/8/3K4/5k2/8/8 w - - 0 1
  // FEN 14: 8/8/8/8/3K4/1k6/8/8 w - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckKing(3, 3));
}

//
// test isCheckKing on black's turn to move
//
TEST(Board, BlackOnCheckFromKing)
{
  auto fenList = readFen("fen/blackOnCheckFromKing.fen");
  auto it1 = fenList.cbegin();
  auto it2 = it1+8;
  auto itend = fenList.cend();

  // FEN 1: 8/8/8/4K3/3k4/8/8/8 b - - 0 1
  // FEN 2: 8/8/8/3K4/3k4/8/8/8 b - - 0 1
  // FEN 3: 8/8/8/2K5/3k4/8/8/8 b - - 0 1
  // FEN 4: 8/8/8/8/2Kk4/8/8/8 b - - 0 1
  // FEN 5: 8/8/8/8/3kK3/8/8/8 b - - 0 1
  // FEN 6: 8/8/8/8/3k4/4K3/8/8 b - - 0 1
  // FEN 7: 8/8/8/8/3k4/3K4/8/8 b - - 0 1
  // FEN 8: 8/8/8/8/3k4/2K5/8/8 b - - 0 1
  while (it1 != it2)
    EXPECT_TRUE((it1++)->boardPtr()->isCheckKing(3, 3));

  // FEN 9: 8/8/8/5K2/3k4/8/8/8 b - - 0 1
  // FEN 10: 8/8/8/1K6/3k4/8/8/8 b - - 0 1
  // FEN 11: 8/8/8/8/1K1k4/8/8/8 b - - 0 1
  // FEN 12: 8/8/8/8/3k1K2/8/8/8 b - - 0 1
  // FEN 13: 8/8/8/8/3k4/5K2/8/8 b - - 0 1
  // FEN 14: 8/8/8/8/3k4/1K6/8/8 b - - 0 1
  while (it1 != itend)
    EXPECT_FALSE((it1++)->boardPtr()->isCheckKing(3, 3));
}

//
// test isCheck
//
TEST(Board, DISABLED_IsCheck)
{
  // TODO
}

//
// test isEnPassant on white's turn
//
TEST(Board, IsEnPassantForWhite)
{
  auto fenList = readFen("fen/enPassantForWhite.fen");

  EXPECT_EQ(16, fenList.size());

  for (int col = 0, i = 0; col < 8; ++col, i += 2) {
    auto pb = fenList[i].boardPtr();
    EXPECT_TRUE(pb->isEnPassant(Color::W, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
    pb = fenList[i+1].boardPtr();
    EXPECT_FALSE(pb->isEnPassant(Color::W, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
  }
}

//
// test isEnPassant on black's turn
//
TEST(Board, IsEnPassantForBlack)
{
  auto fenList = readFen("fen/enPassantForBlack.fen");

  EXPECT_EQ(16, fenList.size());

  for (int col = 0, i = 0; col < 8; ++col, i += 2) {
    auto pb = fenList[i].boardPtr();
    EXPECT_TRUE(pb->isEnPassant(Color::B, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
    pb = fenList[i+1].boardPtr();
    EXPECT_FALSE(pb->isEnPassant(Color::B, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
  }
}

//
// test movePawn on white's turn
//
TEST(Board, MoveWhitePawn)
{
  auto fenList = readFen("fen/moveWhitePawn.fen");

  vector<PieceMove> moveList;
  auto wpawn = Color::W | Piece::P;

  // FEN 1: k7/p7/8/8/8/2p5/1P6/4K3 w - - 0 40
  moveList.emplace_back(1, 1, wpawn, 2, 1);
  moveList.emplace_back(1, 1, wpawn, 3, 1);
  moveList.emplace_back(1, 1, wpawn, 2, 2);
  moveList.back().xPiece(2, 2, Piece::P, Color::B);
  auto pb = fenList[0].boardPtr();
  auto pawnMoveList = pb->movePawn(1, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  auto ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 2: k7/p7/8/8/8/r1p5/1P6/4K3 w - - 0 40
  moveList.emplace_back(1, 1, wpawn, 2, 0);
  moveList.back().xPiece(2, 0, Piece::R, Color::B);
  pb = fenList[1].boardPtr();
  pawnMoveList = pb->movePawn(1, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 3: k7/p7/8/8/8/1p6/1P6/4K3 w - - 0 40
  pb = fenList[2].boardPtr();
  EXPECT_EQ(0, pb->movePawn(1, 1).size());

  // FEN 4: k7/p7/8/8/8/1P6/8/4K3 w - - 0 40
  pb = fenList[3].boardPtr();
  pawnMoveList = pb->movePawn(2, 1);
  EXPECT_EQ(1, pawnMoveList.size());
  EXPECT_EQ(PieceMove(2, 1, wpawn, 3, 1), pawnMoveList.front());

  // FEN 5: k7/8/p7/1Pp5/8/8/8/4K3 w - c6 0 40
  moveList.clear();
  moveList.emplace_back(4, 1, wpawn, 5, 0);
  moveList.back().xPiece(5, 0, Piece::P, Color::B);
  moveList.emplace_back(4, 1, wpawn, 5, 1);
  moveList.emplace_back(4, 1, wpawn, 5, 2);
  moveList.back().xPiece(4, 2, Piece::P, Color::B);
  pb = fenList[4].boardPtr();
  pawnMoveList = pb->movePawn(4, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList) {
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it))
      << "\tPieceMove not found: " << it
      << "\n\tisEnPassant(white, 2): "
      << pb->isEnPassant(Color::W, 2);
  }
}

//
// test movePawn on black's turn
//
TEST(Board, MoveBlackPawn)
{
  auto fenList = readFen("fen/moveBlackPawn.fen");

  vector<PieceMove> moveList;
  auto bpawn = Color::B | Piece::P;

  // FEN 1: 4k3/1p6/2P5/8/8/8/P7/K7 b - - 0 1
  moveList.emplace_back(6, 1, bpawn, 5, 1);
  moveList.emplace_back(6, 1, bpawn, 4, 1);
  moveList.emplace_back(6, 1, bpawn, 5, 2);
  moveList.back().xPiece(5, 2, Piece::P, Color::W);
  auto pb = fenList[0].boardPtr();
  auto pawnMoveList = pb->movePawn(6, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  auto ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 2: 4k3/1p6/R1P5/8/8/8/P7/K7 b - - 0 1
  moveList.emplace_back(6, 1, bpawn, 5, 0);
  moveList.back().xPiece(5, 0, Piece::R, Color::W);
  pb = fenList[1].boardPtr();
  pawnMoveList = pb->movePawn(6, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 3: 4k3/1p6/1P6/8/8/8/P7/K7 b - - 0 1
  pb = fenList[2].boardPtr();
  EXPECT_EQ(0, pb->movePawn(6, 1).size());

  // FEN 4: 4k3/8/1p6/8/8/8/P7/K7 b - - 0 1
  pb = fenList[3].boardPtr();
  pawnMoveList = pb->movePawn(5, 1);
  EXPECT_EQ(1, pawnMoveList.size());
  EXPECT_EQ(PieceMove(5, 1, bpawn, 4, 1), pawnMoveList.front());

  // FEN 5: 4k3/8/8/8/1pP5/P7/8/K7 b - c6 0 1
  moveList.clear();
  moveList.emplace_back(3, 1, bpawn, 2, 0);
  moveList.back().xPiece(2, 0, Piece::P, Color::W);
  moveList.emplace_back(3, 1, bpawn, 2, 1);
  moveList.emplace_back(3, 1, bpawn, 2, 2);
  moveList.back().xPiece(3, 2, Piece::P, Color::W);
  pb = fenList[4].boardPtr();
  pawnMoveList = pb->movePawn(3, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList) {
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it))
      << "\tPieceMove not found: " << it
      << "\n\tisEnPassant(black, 2): "
      << pb->isEnPassant(Color::B, 2);
  }
}

//
// test moveKnight
//
TEST(Board, DISABLED_MoveKnight)
{
  // TODO
}

//
// test moveBishop
//
TEST(Board, DISABLED_MoveBishop)
{
  // TODO
}

//
// test moveRook
//
TEST(Board, DISABLED_MoveRook)
{
  // TODO
}

//
// test moveQueen
//
TEST(Board, DISABLED_MoveQueen)
{
  // TODO
}

//
// test moveKing
//
TEST(Board, DISABLED_MoveKing)
{
  // TODO
}

//
// test toString
//
TEST(Board, DISABLED_ToString)
{
  // TODO
}

//
// test hashCode
//
TEST(Board, DISABLED_HashCode)
{
  // TODO
}

//
// test colorToMove
//
TEST(Board, DISABLED_NextTurn)
{
  // TODO
}

//
// test equality operator
//
TEST(Board, DISABLED_EqualOp)
{
  // TODO
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
