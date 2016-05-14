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
// test canCastle
//
TEST(Board, CanCastle)
{
  vector<FenRecord> fenList = readFen("fen/castling.fen");
  EXPECT_EQ(5, fenList.size());

  auto pb = fenList[0].boardPtr();
  EXPECT_TRUE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  pb = fenList[1].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  pb = fenList[2].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_FALSE(pb->canCastleLong());

  pb = fenList[3].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());

  pb = fenList[4].boardPtr();
  EXPECT_FALSE(pb->canCastle());
  EXPECT_TRUE(pb->canCastleLong());
}

//
// test canCastleLong
//
TEST(Board, CanCastleLong)
{
  Board board;
  EXPECT_FALSE(board.canCastleLong());

  // TODO
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
