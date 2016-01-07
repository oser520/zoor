/**
 * @file tsquare.cc
 * @author Omar A Serrano
 * @date 2016-01-05
 */

#include "square.hh"
#include "gtest/gtest.h"

using zoor::Square;
using zoor::PieceCode;
using zoor::PieceColor;

namespace {

class SquareTest: public testing::Test
{
protected:
  virtual void SetUp()
  {
    s00.setRow(0);
    s00.setColumn(0); 

    s11.setRow(1);
    s11.setColumn(1); 
  }

  Square s00;
  Square s11;
};

TEST_F(SquareTest, InitCorrectly)
{
  EXPECT_EQ(0, s00.row());
  EXPECT_EQ(0, s00.column());
  EXPECT_EQ(1, s11.row());
  EXPECT_EQ(1, s11.column());
}

TEST_F(SquareTest, EqualityOpWork)
{
  EXPECT_NEQ(s11, s00);
}

TEST_F(SquareTest, GettersWork)
{
  EXPECT_EQ(PieceCode::NONE, s00.piece());
  EXPECT_NEQ(PieceCode::KING, s11.piece());
  EXPECT_EQ(PieceColor::NONE, s00.color());
  EXPECT_NEQ(PieceColor::BLACK, s11.color());
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
