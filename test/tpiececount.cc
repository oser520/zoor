/**
 * @file tpiececode.cc
 * @author Omar A Serrano
 * @date 2016-01-09
 */

#include <string>
#include <sstream>
#include "piececode.hh"
#include "piececount.hh"
#include "gtest/gtest.h"

namespace {

using std::string;
using std::ostringstream;
using zoor::PieceCode;
using zoor::PieceCount;

/**
 * Test the default constructor yields a board with the default number of pieces.
 */
TEST(PieceCount1, CtorValues)
{
  PieceCount cp;
  EXPECT_EQ(1, cp.kings()); 
  EXPECT_EQ(1, cp.queens()); 
  EXPECT_EQ(2, cp.rooks()); 
  EXPECT_EQ(2, cp.bishops()); 
  EXPECT_EQ(2, cp.knights()); 
  EXPECT_EQ(8, cp.pawns()); 
}

/**
 * Test PieceCount::init().
 */
TEST(PieceCount2, InitFn)
{
  PieceCount cp;
  cp.setCount(PieceCode::KING, 5);
  cp.setCount(PieceCode::ROOK, 1);
  cp.setCount(PieceCode::PAWN, 1);
  cp.init();
  EXPECT_EQ(1, cp.kings());
  EXPECT_EQ(1, cp.queens());
  EXPECT_EQ(2, cp.rooks());
  EXPECT_EQ(2, cp.bishops());
  EXPECT_EQ(2, cp.knights());
  EXPECT_EQ(8, cp.pawns());
}

/**
 * Test PieceCount::clear().
 */
TEST(PieceCount3, ClearFn)
{
  PieceCount cp;
  cp.clear();
  EXPECT_EQ(0, cp.kings());
  EXPECT_EQ(0, cp.queens());
  EXPECT_EQ(0, cp.rooks());
  EXPECT_EQ(0, cp.bishops());
  EXPECT_EQ(0, cp.knights());
  EXPECT_EQ(0, cp.pawns());
}

/**
 * Test PieceCount::plus().
 */
TEST(PieceCount4, PlusFn)
{
  PieceCount cp;

  cp.plus(PieceCode::PAWN);
  cp.plus(PieceCode::KING);
  cp.plus(PieceCode::ROOK);
  EXPECT_EQ(9, cp.pawns());
  EXPECT_EQ(2, cp.kings());
  EXPECT_EQ(3, cp.rooks());

  cp.plus(PieceCode::QUEEN, 6);
  cp.plus(PieceCode::BISHOP, 5);
  EXPECT_EQ(7, cp.queens());
  EXPECT_EQ(7, cp.bishops());
}

/**
 * Test PieceCount::minus().
 */
TEST(PieceCount5, MinusFn)
{
  PieceCount cp;
  cp.minus(PieceCode::ROOK);
  cp.minus(PieceCode::PAWN, 3);
  EXPECT_EQ(1, cp.rooks());
  EXPECT_EQ(5, cp.pawns());
}

/**
 * Test PieceCount::setCount().
 */
TEST(PieceCount6, SetCountFn)
{
  PieceCount cp;
  cp.clear();
  cp.setCount(PieceCode::ROOK, 7);
  cp.setCount(PieceCode::PAWN, 3);
  EXPECT_EQ(7, cp.rooks());
  EXPECT_EQ(3, cp.pawns());
}

/**
 * Test equality and non-equality operators.
 */
TEST(PieceCount7, EqualityOp)
{
  PieceCount cp1, cp2;
  EXPECT_TRUE(cp1 == cp2);
  EXPECT_FALSE(cp1 != cp2);

  cp2.setCount(PieceCode::PAWN, 5);
  EXPECT_FALSE(cp1 == cp2);
  EXPECT_TRUE(cp1 != cp2);
}

/**
 * Test the value functions.
 */
TEST(PieceCount8, ValueFn)
{
  PieceCount cp;
  EXPECT_EQ(8, cp.valuePawns());
  EXPECT_EQ(6, cp.valueKnights());
  EXPECT_EQ(6, cp.valueBishops());
  EXPECT_EQ(10, cp.valueRooks());
  EXPECT_EQ(9, cp.valueQueens());
}

/**
 * Test the addition and assignment operator functions.
 */
TEST(PieceCount9, opPlusAssign)
{
  PieceCount cp;

  cp += PieceCode::PAWN;
  EXPECT_EQ(9, cp.pawns());

  cp += PiecCode::KNIGHT;
  cp += PiecCode::KNIGHT;
  EXPECT_EQ(4, cp.knights());

  cp += PieceCode::BISHOP;
  EXPECT_EQ(3, cp.bishop());

  cp += PieceCode::ROOK;
  EXPECT_EQ(3, cp.rooks());

  cp += PieceCode::QUEEN;
  EXPECT_EQ(2, cp.queens());

  cp += PieceCode::KING;
  EXPECT_EQ(2, cp.kings());
}

/**
 * Test the output operator.
 */
TEST(PieceCount10, OutputOp) {
  PieceCount cp;
  ostringstream ss1;
  ss1 << cp;
  string s("{kings=1, queens=1, rooks=2, bishops=2, knights=2, pawns=8}");
  
  EXPECT_EQ(s, ss1.str()); 
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
