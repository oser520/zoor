/////////////////////////////////////////////////////////////////////////////////////
/// @file tboard.cc
/// @author Omar A Serrano
/// @date 2016-03-19
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <string>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "piecemove.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
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
// test canCastle
//
TEST(Board, CanCastle)
{
  Board board;
  EXPECT_FALSE(board.canCastle());

  // TODO
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
