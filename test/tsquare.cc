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

TEST(SquareTest, DefaultCtor)
{
  Square s;
  EXPECT_EQ(0, s.row());
  EXPECT_EQ(0, s.column());
  EXPECT_EQ(PieceCode::NONE, s.piece());
  EXPECT_EQ(PieceColor::NONE, s.color());
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

TEST(SquareTest, GettersWork)
{
  Square s;
  s.setPiece(PieceCode::KING).setColor(PieceColor::WHITE).setRow(5).setColumn(7);
  EXPECT_EQ(PieceCode::KING, s.piece());
  EXPECT_EQ(PieceColor::WHITE, s.color());
  EXPECT_EQ(5, s.row());
  EXPECT_EQ(7, s.column());

  EXPECT_NE(PieceCode::BISHOP, s.piece());
  EXPECT_NE(PieceColor::BLACK, s.color());
  EXPECT_NE(1, s.row());
  EXPECT_NE(3, s.column());
}

TEST_F(SquareTest, SettersWork)
{
  s00.setPiece(PieceCode::PAWN)
     .setColor(PieceColor::BLACK)
     .setRow(5)
     .setColumn(7);

  EXPECT_EQ(PieceCode::PAWN, s00.piece());
  EXPECT_EQ(PieceColor::BLACK, s00.color());
  EXPECT_EQ(5, s00.row());
  EXPECT_EQ(7, s00.column());

  EXPECT_NE(PieceCode::QUEEN, s00.piece());
  EXPECT_NE(PieceColor::WHITE, s00.color());
  EXPECT_NE(7, s00.row());
  EXPECT_NE(5, s00.column());
}

TEST_F(SquareTest, BoolsWork) {
  s00.setPiece(PieceCode::KNIGHT)
     .setColor(PieceColor::BLACK)
     .setRow(5)
     .setColumn(7);
  s11.setPiece(PieceCode::KNIGHT)
     .setColor(PieceColor::BLACK)
     .setRow(5)
     .setColumn(7);
  EXPECT_TRUE(s00 == s11);
  EXPECT_FALSE(s00 != s11);

  s11.setPiece(PieceCode::KNIGHT)
     .setColor(PieceColor::WHITE)
     .setRow(5)
     .setColumn(7);
  EXPECT_FALSE(s00 == s11);
  EXPECT_TRUE(s00 != s11);
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
