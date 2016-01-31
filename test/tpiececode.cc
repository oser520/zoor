/**
 * @file tpiececode.cc
 * @author Omar A Serrano
 * @date 2016-01-09
 */

// TODO: add unit tests for getPieceCode and getPieceColor

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
  ostringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7;
  ss1 << PieceCode::NONE; 
  ss2 << PieceCode::PAWN; 
  ss3 << PieceCode::KNIGHT; 
  ss4 << PieceCode::BISHOP; 
  ss5 << PieceCode::ROOK; 
  ss6 << PieceCode::QUEEN; 
  ss7 << PieceCode::KING; 
  
  EXPECT_STREQ("NONE", ss1.str().c_str()); 
  EXPECT_STREQ("PAWN", ss2.str().c_str()); 
  EXPECT_STREQ("KNIGHT", ss3.str().c_str()); 
  EXPECT_STREQ("BISHOP", ss4.str().c_str()); 
  EXPECT_STREQ("ROOK", ss5.str().c_str()); 
  EXPECT_STREQ("QUEEN", ss6.str().c_str()); 
  EXPECT_STREQ("KING", ss7.str().c_str()); 
}

TEST(PieceColorTest, PieceColor)
{
  ostringstream ss1, ss2, ss3;
  ss1 << PieceColor::NONE; 
  ss2 << PieceColor::WHITE; 
  ss3 << PieceColor::BLACK; 
  
  EXPECT_STREQ("NONE", ss1.str().c_str()); 
  EXPECT_STREQ("WHITE", ss2.str().c_str()); 
  EXPECT_STREQ("BLACK", ss3.str().c_str()); 
}

TEST(PieceValueTest, PieceValue)
{
  using uchar = unsigned char;
  EXPECT_EQ(static_cast<uchar>(0), static_cast<uchar>(PieceValue::NONE)); 
  EXPECT_EQ(static_cast<uchar>(1), static_cast<uchar>(PieceValue::PAWN)); 
  EXPECT_EQ(static_cast<uchar>(3), static_cast<uchar>(PieceValue::KNIGHT)); 
  EXPECT_EQ(static_cast<uchar>(3), static_cast<uchar>(PieceValue::BISHOP)); 
  EXPECT_EQ(static_cast<uchar>(5), static_cast<uchar>(PieceValue::ROOK)); 
  EXPECT_EQ(static_cast<uchar>(9), static_cast<uchar>(PieceValue::QUEEN)); 
  EXPECT_EQ(static_cast<uchar>(0xffff), static_cast<uchar>(PieceValue::KING)); 
}

TEST(PieceMaskTest, OutputOp)
{
  ostringstream ss1, ss2;
  ss1 << PieceMask::PIECE;
  ss2 << PieceMask::COLOR;

  EXPECT_STREQ("0x7", ss1.str().c_str());
  EXPECT_STREQ("0x18", ss2.str().c_str());
}

TEST(PieceAndColor, LogicOpAnd)
{
  piececode_t pcolor = static_cast<piececode_t>(PieceColor::NONE);
  piececode_t pcode = static_cast<piececode_t>(PieceCode::PAWN);
  EXPECT_EQ(pcolor & pcode, PieceColor::NONE & PieceCode::PAWN);

  pcolor = static_cast<piececode_t>(PieceColor::WHITE);
  pcode = static_cast<piececode_t>(PieceCode::ROOK);
  EXPECT_EQ(pcolor & pcode, PieceColor::WHITE & PieceCode::ROOK);

  pcolor = static_cast<piececode_t>(PieceColor::BLACK);
  pcode = static_cast<piececode_t>(PieceCode::BISHOP);
  EXPECT_EQ(pcolor & pcode, PieceColor::BLACK & PieceCode::BISHOP);
}

TEST(PieceColorNot, LogicOpNot)
{
  EXPECT_EQ(PieceColor::NONE, ~PieceColor::NONE);
  EXPECT_EQ(PieceColor::BLACK, ~PieceColor::WHITE);
  EXPECT_EQ(PieceColor::WHITE, ~PieceColor::BLACK);
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
