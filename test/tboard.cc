/////////////////////////////////////////////////////////////////////////////////////
/// @file tboard.cc
/// @author Omar A Serrano
/// @date 2016-03-19
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <string>
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

  // FEN record --> k7/8/8/8/4n3/8/8/R3K2R w KQ - 0 40
  auto pb = fenList[0].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/4n3/R3K2R w KQ - 0 40
  pb = fenList[1].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/4n3/8/R3K2R w KQ - 0 40
  pb = fenList[2].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/7n/R3K2R w KQ - 0 40
  pb = fenList[3].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/6n1/8/R3K2R w KQ - 0 40
  pb = fenList[4].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/n7/R3K2R w KQ - 0 40
  pb = fenList[5].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/b7/R3K2R w KQ - 0 40
  pb = fenList[6].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/4b3/8/R3K2R w KQ - 0 40
  pb = fenList[7].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/4b3/8/8/R3K2R w KQ - 0 40
  pb = fenList[8].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/7b/8/R3K2R w KQ - 0 40
  pb = fenList[9].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/b7/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[10].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/4r3/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[11].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/5r2/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[12].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/7r/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[13].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/2r3r1/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[14].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/7q/8/R3K2R w KQ - 0 40
  pb = fenList[15].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/7q/8/8/R3K2R w KQ - 0 40
  pb = fenList[16].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/7q/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[17].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/7q/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[18].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/7q/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[19].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/4q3/8/8/8/8/8/R3K2R w KQ - 0 40
  pb = fenList[20].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/8/Rq2K2R w KQ - 0 40
  pb = fenList[21].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/7p/R3K2R w KQ - 0 40
  pb = fenList[22].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/7p/8/R3K2R w KQ - 0 40
  pb = fenList[23].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/4p3/R3K2R w KQ - 0 40
  pb = fenList[24].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> k7/8/8/8/8/8/2p5/R3K2R w KQ - 0 40
  pb = fenList[25].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> 8/8/8/8/8/8/1k6/R3K2R w KQ - 0 40
  pb = fenList[26].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> 8/8/8/8/8/8/6k1/R3K2R w KQ - 0 40
  pb = fenList[27].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> 8/8/8/8/8/6k1/8/R3K2R w KQ - 0 40
  pb = fenList[28].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());
}

//
// test canBlackCastle
//
TEST(Board, CanBlackCastle)
{
  vector<FenRecord> fenList = readFen("fen/canBlackCastle.fen");

  // FEN record --> r3k2r/8/8/4N3/8/8/8/7K b kq - 0 40
  auto pb = fenList[0].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/4N3/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[1].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/4N3/8/8/8/8/7K b kq - 0 40
  pb = fenList[2].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/7N/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[3].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/6N1/8/8/8/8/7K b kq - 0 40
  pb = fenList[4].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/N7/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[5].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/B7/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[6].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/4B3/8/8/8/8/7K b kq - 0 40
  pb = fenList[7].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/4B3/8/8/8/7K b kq - 0 40
  pb = fenList[8].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/7B/8/8/8/8/7K b kq - 0 40
  pb = fenList[9].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/B7/8/8/7K b kq - 0 40
  pb = fenList[10].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/4R3/7K b kq - 0 40
  pb = fenList[11].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/5R2/7K b kq - 0 40
  pb = fenList[12].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/7R/7K b kq - 0 40
  pb = fenList[13].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/2R3R1/7K b kq - 0 40
  pb = fenList[14].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/7Q/8/8/8/8/7K b kq - 0 40
  pb = fenList[15].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/7Q/8/8/8/7K b kq - 0 40
  pb = fenList[16].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/7Q/8/8/7K b kq - 0 40
  pb = fenList[17].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/7Q/8/7K b kq - 0 40
  pb = fenList[18].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/7Q/7K b kq - 0 40
  pb = fenList[19].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/8/8/8/8/4Q3/7K b kq - 0 40
  pb = fenList[20].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> rQ2k2r/8/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[21].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/7P/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[22].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/7P/8/8/8/8/7K b kq - 0 40
  pb = fenList[23].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/4P3/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[24].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/2P5/8/8/8/8/8/7K b kq - 0 40
  pb = fenList[25].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/1K6/8/8/8/8/8/8 b kq - 0 40
  pb = fenList[26].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  // FEN record --> r3k2r/6K1/8/8/8/8/8/8 b kq - 0 40
  pb = fenList[27].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  // FEN record --> r3k2r/8/6K1/8/8/8/8/8 b kq - 0 40
  pb = fenList[28].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());
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
// test operator()
//
TEST(Board, DISABLED_CallOp)
{
  // TODO
}

//
// test begin
//
TEST(Board, DISABLED_Begin)
{
  // TODO
}

//
// test end
//
TEST(Board, DISABLED_End)
{
  // TODO
}

//
// test jump
//
TEST(Board, DISABLED_Jump)
{
  // TODO
}

//
// test isCheckPawn
//
TEST(Board, DISABLED_IsCheckPawn)
{
  // TODO
}

//
// test isCheckKnight
//
TEST(Board, DISABLED_IsCheckKnight)
{
  // TODO
}

//
// test isCheckBishop
//
TEST(Board, DISABLED_IsCheckBishop)
{
  // TODO
}

//
// test isCheckRook
//
TEST(Board, DISABLED_IsCheckRook)
{
  // TODO
}

//
// test isCheckQueen
//
TEST(Board, DISABLED_IsCheckQueen)
{
  // TODO
}

//
// test isCheckKing
//
TEST(Board, DISABLED_IsCheckKing)
{
  // TODO
}

//
// test isCheck
//
TEST(Board, DISABLED_IsCheck)
{
  // TODO
}

//
// test isEnPassant
//
TEST(Board, DISABLED_IsEnPassant)
{
  // TODO
}

//
// test movePawn
//
TEST(Board, DISABLED_MovePawn)
{
  // TODO
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
