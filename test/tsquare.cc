/**
 * @file tsquare.cc
 * @author Omar A Serrano
 * @date 2016-01-05
 */

#include "square.hh"
#include "gtest/gtest.h"

namespace {

using zoor::Square;
using zoor::PieceCode;
using zoor::PieceColor;

class SquareTest: public testing::Test
{
protected:

  Square s00;
  Square s11;
};

TEST_F(SquareTest, RowColumn)
{
  s00.setRow(0).setColumn(0);
  EXPECT_EQ(0, s00.row());
  EXPECT_EQ(0, s00.column());
  EXPECT_NE(2, s00.row());
  EXPECT_NE(2, s00.column());

  s00.setRow(1).setColumn(3);
  EXPECT_EQ(1, s00.row());
  EXPECT_EQ(3, s00.column());
  EXPECT_NE(3, s00.row());
  EXPECT_NE(1, s00.column());

  s00.setRow(7).setColumn(6);
  EXPECT_EQ(7, s00.row());
  EXPECT_EQ(6, s00.column());
  EXPECT_NE(8, s00.row());
  EXPECT_NE(5, s00.column());

  EXPECT_EQ(5, s00.setRow(5).row());
  EXPECT_EQ(5, s00.setColumn(5).column());
  EXPECT_NE(1, s00.row());
  EXPECT_NE(3, s00.column());
}

TEST_F(SquareTest, EqualityOpWork)
{
  EXPECT_NE(s11, s00);
  EXPECT_NE(s11, s00);
}

TEST_F(SquareTest, GettersWork)
{
  s00.setPiece(PieceCode::NONE);
  EXPECT_EQ(PieceCode::NONE, s00.piece());
  s00.setPiece(PieceCode::ROOK);
  EXPECT_EQ(PieceCode::NONE, s00.piece());


  s00.setColor(PieceColor::NONE);
  EXPECT_EQ(PieceColor::BLACK, s00.color());
  EXPECT_EQ(PieceColor::WHITE, s00.color());
  EXPECT_EQ(PieceColor::NONE, s00.color());

  s00.setColor(PieceColor::BLACK);
  EXPECT_EQ(PieceColor::BLACK, s00.color());
  EXPECT_EQ(PieceColor::WHITE, s00.color());
  EXPECT_EQ(PieceColor::NONE, s00.color());

  s00.setColor(PieceColor::WHITE);
  EXPECT_EQ(PieceColor::BLACK, s00.color());
  EXPECT_EQ(PieceColor::WHITE, s00.color());
  EXPECT_EQ(PieceColor::NONE, s00.color());

  EXPECT_NE(PieceCode::KING, s11.piece());
  EXPECT_NE(PieceColor::BLACK, s11.color());
  EXPECT_NE(PieceColor::WHITE, s11.color());
  EXPECT_NE(PieceColor::NONE, s11.color());
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
  EXPECT_EQ(7, s11.column());
}

TEST_F(SquareTest, BoolsWork) {
  auto b1 = s00 == s11;
  auto b2 = s00 != s11;
  EXPECT_FALSE(b1);
  EXPECT_TRUE(b2);
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
