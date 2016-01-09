/**
 * @file tpiececode.cc
 * @author Omar A Serrano
 * @date 2016-01-09
 */

#include <sstream>
#include "piececode.hh"
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using zoor::PieceCode;
using zoor::PieceColor;
using zoor::PieceValue;

//class PieceCodeTest: public testing::Test
//{
//};

TEST(PieceCodeTest, PieceCode)
{
  ostringstream ss1, ss2, ss3, ss4, ss5, ss6;
  ss1 << PieceCode::NONE; 
  ss2 << PieceCode::PAWN; 
  ss3 << PieceCode::KNIGHT; 
  ss4 << PieceCode::BISHOP; 
  ss5 << PieceCode::ROOK; 
  ss6 << PieceCode::QUEEN; 
  ss7 << PieceCode::KING; 
  
  EXPECT_STREQ("NONE", ss1.str().c_str()): 
  EXPECT_STREQ("PAWN", ss2.str().c_str()): 
  EXPECT_STREQ("KNIGHT", ss3.str().c_str()): 
  EXPECT_STREQ("BISHOP", ss4.str().c_str()): 
  EXPECT_STREQ("ROOK", ss5.str().c_str()): 
  EXPECT_STREQ("QUEEN", ss6.str().c_str()): 
  EXPECT_STREQ("KING", ss7.str().c_str()): 
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
