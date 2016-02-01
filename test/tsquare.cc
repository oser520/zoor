/**
 * @file tsquare.cc
 * @author Omar A Serrano
 * @date 2016-01-05
 */

// TODO: test new constructor with piececode_t parameter
// TODO: test setPieceCode
// TODO: test setLocation

#include "square.hh"
#include "gtest/gtest.h"

namespace {

using zoor::Square;
using zoor::PieceCode;
using zoor::PieceColor;

/**
 * Test for default ctor.
 */
TEST(SquareTest, DefaultCtor)
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
TEST(SquareTest, Ctor2Param)
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
TEST(SquareTest, Ctor3Param)
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
TEST(SquareTest, Ctor3Param)
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
TEST(SquareTest, Getters)
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
TEST(SquareTest, Setters)
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

TEST(SquareTest, BoolsWork) {
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

TEST(SquareTest, EqualityOpWork)
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
}


} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
