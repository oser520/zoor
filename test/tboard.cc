/**
 * @file tboard.cc
 * @author Omar A Serrano
 * @date 2016-03-19
 */

#include <string>
#include "piececode.hh"
#include "square.hh"
#include "piecemove.hh"
#include "board.hh"
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using namespace zoor;

// test Board default ctor
// TODO: enable test
TEST(Board1, Ctor)
{
  Board board;
  EXPECT_FALSE(board.canCastle());
  EXPECT_FALSE(board.canCastleLong());
  EXPECT_EQ(PieceColor::WHITE, board.colorToMove());

  auto sq = board(0, 0);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
  EXPECT_EQ(PieceCode::ROOK, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());

  sq = board(6, 2);
  EXPECT_EQ(6, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(PieceCode::PAWN, sq.piece());
  EXPECT_EQ(PieceColor::BLACK, sq.color());

  sq = board(7, 2);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(PieceCode::BISHOP, sq.piece());
  EXPECT_EQ(PieceColor::BLACK, sq.color());

  sq = board(0, 3);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(3, sq.column());
  EXPECT_EQ(PieceCode::QUEEN, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());

  sq = board(7, 4);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(4, sq.column());
  EXPECT_EQ(PieceCode::KING, sq.piece());
  EXPECT_EQ(PieceColor::BLACK, sq.color());

  sq = board(0, 5);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(PieceCode::BISHOP, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());

  sq = board(7, 6);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(6, sq.column());
  EXPECT_EQ(PieceCode::KNIGHT, sq.piece());
  EXPECT_EQ(PieceColor::BLACK, sq.color());

  sq = board(0, 7);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(6, sq.column());
  EXPECT_EQ(PieceCode::ROOK, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());

  sq = board(4, 5);
  EXPECT_EQ(4, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
}

// test isInBound
TEST(Board2, isInBound)
{
  EXPECT_TRUE(Board::isInBound(6));
  EXPECT_TRUE(Board::isInBound(1,3));

  EXPECT_FALSE(Board::isInBound(9));
  EXPECT_FALSE(Board::isInBound(3, 8));
}

// test canCastle
TEST(Board3, canCastle)
{
  Board board;
  EXPECT_FALSE(board.canCastle());

  // TODO: make different tests
  // while on check
  // gets on check when it moves
  // legal move
  // after moving king
  // after moving rook
  // repeat for black and white
}

// test canCastleLong
TEST(Board4, canCastleLong)
{
  Board board;
  EXPECT_FALSE(board.canCastleLong());

  // TODO: make different tests
  // while on check
  // gets on check when it moves
  // legal move
  // after moving king
  // after moving rook
  // repeat for black and white
}

// test getMoves with row and column specified
// TODO: enable test
TEST(Board5, DISABLED_getMovesRowCol)
{
  // TODO: try different scenarios
}

// test getMoves for all moves on the board
// TODO: enable test
TEST(Board6, DISABLED_getMoves)
{
  // TODO: try different scenarios
}

// test getBoards
// TODO: enable test
TEST(Board7, DISABLED_getBoards)
{
  // TODO: try different scenarios
}

// test makeMoveCopy
// TODO: enable test
TEST(Board8, DISABLED_makeMoveCopy)
{
  // TODO: try different scenarios
}

// test makeMove
// TODO: enable test
TEST(Board9, DISABLED_makeMove)
{
  // TODO: try different scenarios
}

// test lastMove
// TODO: enable test
TEST(Board10, DISABLED_lastMove)
{
  // TODO: try different scenarios
}

// test operator()
// TODO: enable test
TEST(Board11, DISABLED_callOp)
{
  // TODO: try different scenarios
}

// test begin
// TODO: enable test
TEST(Board12, DISABLED_begin)
{
  // TODO: try different scenarios
}

// test end
// TODO: enable test
TEST(Board13, DISABLED_end)
{
  // TODO: try different scenarios
}

// test jump
// TODO: enable test
TEST(Board14, DISABLED_jump)
{
  // TODO: try different scenarios
}

// test isCheckPawn
// TODO: enable test
TEST(Board15, DISABLED_isCheckPawn)
{
  // TODO: try different scenarios
}

// test isCheckKnight
// TODO: enable test
TEST(Board16, DISABLED_isCheckKnight)
{
  // TODO: try different scenarios
}

// test isCheckBishop
// TODO: enable test
TEST(Board17, DISABLED_isCheckBishop)
{
  // TODO: try different scenarios
}

// test isCheckRook
// TODO: enable test
TEST(Board18, DISABLED_isCheckRook)
{
  // TODO: try different scenarios
}

// test isCheckQueen
// TODO: enable test
TEST(Board19, DISABLED_isCheckQueen)
{
  // TODO: try different scenarios
}

// test isCheckKing
// TODO: enable test
TEST(Board20, DISABLED_isCheckKing)
{
  // TODO: try different scenarios
}

// test isCheck
// TODO: enable test
TEST(Board21, DISABLED_isCheck)
{
  // TODO: try different scenarios
}

// test isEnPassant
// TODO: enable test
TEST(Board22, DISABLED_isEnPassant)
{
  // TODO: try different scenarios
}

// test movePawn
// TODO: enable test
TEST(Board23, DISABLED_movePawn)
{
  // TODO: try different scenarios
}

// test moveKnight
// TODO: enable test
TEST(Board24, DISABLED_moveKnight)
{
  // TODO: try different scenarios
}

// test moveBishop
// TODO: enable test
TEST(Board25, DISABLED_moveBishop)
{
  // TODO: try different scenarios
}

// test moveRook
// TODO: enable test
TEST(Board26, DISABLED_moveRook)
{
  // TODO: try different scenarios
}

// test moveQueen
// TODO: enable test
TEST(Board27, DISABLED_moveQueen)
{
  // TODO: try different scenarios
}

// test moveKing
// TODO: enable test
TEST(Board28, DISABLED_moveKing)
{
  // TODO: try different scenarios
}

// test toString
// TODO: enable test
TEST(Board29, DISABLED_toString)
{
  // TODO: try different scenarios
}

// test hashCode
// TODO: enable test
TEST(Board30, DISABLED_hashCode)
{
  // TODO: try different scenarios
}

// test colorToMove
// TODO: enable test
TEST(Board31, DISABLED_colorToMove)
{
  // TODO: try different scenarios
}

// test equality operator
// TODO: enable test
TEST(Board32, DISABLED_EqualityOp)
{
  // TODO: try different scenarios
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

