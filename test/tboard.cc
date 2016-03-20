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
DISABLED_TEST(Board1, Ctor)
{
  Board board;
  // TODO: check that all pieces are lined up correctly
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
DISABLED_TEST(Board5, getMovesRowCol)
{
  // TODO: try different scenarios
}

// test getMoves for all moves on the board
// TODO: enable test
DISABLED_TEST(Board6, getMoves)
{
  // TODO: try different scenarios
}

// test getBoards
// TODO: enable test
DISABLED_TEST(Board7, getBoards)
{
  // TODO: try different scenarios
}

// test makeMoveCopy
// TODO: enable test
DISABLED_TEST(Board8, makeMoveCopy)
{
  // TODO: try different scenarios
}

// test makeMove
// TODO: enable test
DISABLED_TEST(Board9, makeMove)
{
  // TODO: try different scenarios
}

// test lastMove
// TODO: enable test
DISABLED_TEST(Board10, lastMove)
{
  // TODO: try different scenarios
}

// test operator()
// TODO: enable test
DISABLED_TEST(Board11, callOp)
{
  // TODO: try different scenarios
}

// test begin
// TODO: enable test
DISABLED_TEST(Board12, begin)
{
  // TODO: try different scenarios
}

// test end
// TODO: enable test
DISABLED_TEST(Board13, end)
{
  // TODO: try different scenarios
}

// test jump
// TODO: enable test
DISABLED_TEST(Board14, jump)
{
  // TODO: try different scenarios
}

// test isCheckPawn
// TODO: enable test
DISABLED_TEST(Board15, isCheckPawn)
{
  // TODO: try different scenarios
}

// test isCheckKnight
// TODO: enable test
DISABLED_TEST(Board16, isCheckKnight)
{
  // TODO: try different scenarios
}

// test isCheckBishop
// TODO: enable test
DISABLED_TEST(Board17, isCheckBishop)
{
  // TODO: try different scenarios
}

// test isCheckRook
// TODO: enable test
DISABLED_TEST(Board18, isCheckRook)
{
  // TODO: try different scenarios
}

// test isCheckQueen
// TODO: enable test
DISABLED_TEST(Board19, isCheckQueen)
{
  // TODO: try different scenarios
}

// test isCheckKing
// TODO: enable test
DISABLED_TEST(Board20, isCheckKing)
{
  // TODO: try different scenarios
}

// test isCheck
// TODO: enable test
DISABLED_TEST(Board21, isCheck)
{
  // TODO: try different scenarios
}

// test isEnPassant
// TODO: enable test
DISABLED_TEST(Board22, isEnPassant)
{
  // TODO: try different scenarios
}

// test movePawn
// TODO: enable test
DISABLED_TEST(Board23, movePawn)
{
  // TODO: try different scenarios
}

// test moveKnight
// TODO: enable test
DISABLED_TEST(Board24, moveKnight)
{
  // TODO: try different scenarios
}

// test moveBishop
// TODO: enable test
DISABLED_TEST(Board25, moveBishop)
{
  // TODO: try different scenarios
}

// test moveRook
// TODO: enable test
DISABLED_TEST(Board26, moveRook)
{
  // TODO: try different scenarios
}

// test moveQueen
// TODO: enable test
DISABLED_TEST(Board27, moveQueen)
{
  // TODO: try different scenarios
}

// test moveKing
// TODO: enable test
DISABLED_TEST(Board28, moveKing)
{
  // TODO: try different scenarios
}

// test toString
// TODO: enable test
DISABLED_TEST(Board29, toString)
{
  // TODO: try different scenarios
}

// test hashCode
// TODO: enable test
DISABLED_TEST(Board30, hashCode)
{
  // TODO: try different scenarios
}

// test colorToMove
// TODO: enable test
DISABLED_TEST(Board31, colorToMove)
{
  // TODO: try different scenarios
}

// test equality operator
// TODO: enable test
DISABLED_TEST(Board32, EqualityOp)
{
  // TODO: try different scenarios
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

