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
  s00.setPiece(PieceCode::NONE).setColor(PieceColor::NONE).setRow(0).setColumn(0);
  s11.setPiece(PieceCode::NONE).setColor(PieceColor::NONE).setRow(0).setColumn(0);
  EXPECT_EQ(s11, s00);

  s00.setPiece(PieceCode::KNIGHT);
  EXPECT_NE(s11, s00);

  s00.setPiece(PieceCode::NONE);
  s11.setColor(PieceColor::WHITE);
  EXPECT_NE(s11, s00);

  s00.setPiece(PieceCode::ROOK).setColor(PieceColor::BLACK).setRow(5);
  s11.setPiece(PieceCode::ROOK).setColor(PieceColor::BLACK).setRow(3);
  EXPECT_NE(s11, s00);

  s11.setRow(5);
  EXPECT_EQ(s11, s00);
}

TEST_F(SquareTest, GettersWork)
{
  s00.setPiece(PieceCode::KING).setColor(PieceColor::WHITE).setRow(5).setColumn(7);
  EXPECT_EQ(PieceCode::KING, s00.piece());
  EXPECT_EQ(PieceColor::WHITE, s00.color());
  EXPECT_EQ(5, s00.row());
  EXPECT_EQ(7, s00.column());

  EXPECT_NE(PieceCode::BISHOP, s00.piece());
  EXPECT_NE(PieceColor::BLACK, s00.color());
  EXPECT_NE(1, s00.row());
  EXPECT_NE(3, s00.column());
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
