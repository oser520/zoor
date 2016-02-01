/**
 * @file tsquare.cc
 * @author Omar A Serrano
 * @date 2016-01-05
 */

#include "piececode.hh"
#include "square.hh"
#include "gtest/gtest.h"

namespace {

using zoor::Square;
using zoor::PieceCode;
using zoor::PieceColor;
using zoor::getPieceCode;
using zoor::getPieceColor;

/**
 * Test for default ctor.
 */
TEST(SquareTest1, DefaultCtor)
{
  Square s;
  EXPECT_EQ(0, s.row());
  EXPECT_EQ(0, s.column());
  EXPECT_EQ(PieceCode::NONE, s.piece());
  EXPECT_EQ(PieceColor::NONE, s.color());
}

/**
 * Test for ctor with 2 parameters.
 */
TEST(SquareTest2, Ctor2Param)
{
  Square s(3, 5);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(PieceCode::NONE, s.piece());
  EXPECT_EQ(PieceColor::NONE, s.color());
}

/**
 * Test for ctor with 3 parameters.
 */
TEST(SquareTest3, Ctor3Param)
{
  Square s(3, 5, PieceColor::WHITE & PieceCode::BISHOP);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(PieceCode::BISHOP, s.piece());
  EXPECT_EQ(PieceColor::WHITE, s.color());
}

/**
 * Test for ctor with 4 parameters.
 */
TEST(SquareTest4, Ctor3Param)
{
  Square s(3, 5, PieceCode::BISHOP, PieceColor::WHITE);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(PieceCode::BISHOP, s.piece());
  EXPECT_EQ(PieceColor::WHITE, s.color());
}

/**
 * Test getters.
 */
TEST(SquareTest5, Getters)
{
  Square s;
  s.setPiece(PieceCode::KING).setColor(PieceColor::WHITE).setRow(5).setColumn(7);
  EXPECT_EQ(PieceCode::KING, s.piece());
  EXPECT_EQ(PieceColor::WHITE, s.color());
  EXPECT_EQ(5, s.row());
  EXPECT_EQ(7, s.column());
  EXPECT_EQ(PieceColor::WHITE & PieceCode::KING, s.code());

  EXPECT_NE(PieceCode::BISHOP, s.piece());
  EXPECT_NE(PieceColor::BLACK, s.color());
  EXPECT_NE(1, s.row());
  EXPECT_NE(3, s.column());
  EXPECT_EQ(PieceColor::BLACK & PieceCode::ROOK, s.code());
}

/**
 * Test setters.
 */
TEST(SquareTest6, Setters)
{
  Square s;
  s.setPiece(PieceCode::PAWN)
   .setColor(PieceColor::BLACK)
   .setRow(5)
   .setColumn(7);

  EXPECT_EQ(PieceCode::PAWN, s.piece());
  EXPECT_EQ(PieceColor::BLACK, s.color());
  EXPECT_EQ(5, s.row());
  EXPECT_EQ(7, s.column());

  s.setLocation(2, 5);
  EXPECT_NE(7, s.row());
  EXPECT_NE(5, s.column());

  auto pcode = PieceColor::WHITE & PieceCode::QUEEN;
  s.setPieceCode(pcode);
  EXPECT_EQ(PieceCode::QUEEN, s.piece());
  EXPECT_EQ(PieceColor::WHITE, s.color());
  EXPECT_EQ(pcode, s.code());
}

/**
 * Test bools.
 */
TEST(SquareTest7, Bools) {
  Square s1(5, 7, PieceCode::KNIGHT, PieceColor::BLACK);
  Square s2(5, 7, PieceCode::KNIGHT, PieceColor::BLACK);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 != s2);

  s1.setPiece(PieceCode::KNIGHT)
    .setColor(PieceColor::WHITE)
    .setRow(5)
    .setColumn(7);

  EXPECT_FALSE(s1 == s2);
  EXPECT_TRUE(s1 != s2);
}

/**
 * Unit tests for equality operators.
 */
TEST(SquareTest8, EqualityOp)
{
  Square s1, s2;
  EXPECT_EQ(s1, s2);

  s1.setPiece(PieceCode::KNIGHT);
  EXPECT_NE(s1, s2);

  s1.setPiece(PieceCode::NONE);
  s2.setColor(PieceColor::WHITE);
  EXPECT_NE(s1, s2);

  s1.setPiece(PieceCode::ROOK).setColor(PieceColor::BLACK).setRow(5);
  s2.setPiece(PieceCode::ROOK).setColor(PieceColor::BLACK).setRow(3);
  EXPECT_NE(s1, s2);

  s2.setRow(5);
  EXPECT_EQ(s1, s2);

  s1.setLocation(5, 7)
    .setPiece(PieceCode::KNIGHT)
    .setColor(PieceColor::BLACK);
  s2.setLocation(5, 7)
    .setPiece(PieceCode::KNIGHT)
    .setColor(PieceColor::BLACK);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 != s2);

  s1.setColor(PieceColor::WHITE);

  EXPECT_FALSE(s1 == s2);
  EXPECT_TRUE(s1 != s2);
}

} // namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
