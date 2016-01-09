/**
 * @file tpiececode.cc
 * @author Omar A Serrano
 * @date 2016-01-09
 */

#include <sstream>
#include "piececode.hh"
#include "piececount.hh"
#include "gtest/gtest.h"

namespace {

using zoor::PieceCount;
using PieceCount::count_type;

/**
 * Test the default constructor yields a board with the default number of pieces.
 */
TEST(PieceCountTest, CtorValues)
{
  PieceCount cp;
  EXPECT_EQ(1, cp.mKings); 
  EXPECT_EQ(1, cp.mQueens); 
  EXPECT_EQ(2, cp.mRooks); 
  EXPECT_EQ(2, cp.mBishops); 
  EXPECT_EQ(2, cp.mKnights); 
  EXPECT_EQ(8, cp.mPawn); 
  EXPECT_EQ(16, cp.mTotal); 
}

TEST(PieceCountTest, InitFn)
{
  PieceCount cp;
  cp.mKings = 5;
  cp.mRooks = 1;
  cp.mPawns = 1;
  cp.init();
  EXPECT_EQ(1, cp.mKings);
  EXPECT_EQ(1, cp.mQueens);
  EXPECT_EQ(2, cp.mRooks);
  EXPECT_EQ(2, cp.mBishops);
  EXPECT_EQ(2, cp.mKnights);
  EXPECT_EQ(8, cp.mPawn);
  EXPECT_EQ(16, cp.mTotal);
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

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
