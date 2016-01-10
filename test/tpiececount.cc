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
using zoor::PieceCount;

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
  EXPECT_EQ(8, cp.mPawns);
  EXPECT_EQ(16, cp.mTotal);
}

TEST(PieceCountTest, EqualityOp)
{
  PieceCount cp1, cp2;
  EXPECT_TRUE(cp1 == cp2);
  EXPECT_FALSE(cp1 != cp2);

  cp2.mPawns = 5;
  EXPECT_FALSE(cp1 == cp1);
  EXPECT_TRUE(cp1 != cp1);
}

TEST(PieceCountTest, ValueFn)
{
  PieceCount cp;
  EXPECT_EQ(8, cp.valuePawns());
  EXPECT_EQ(6, cp.valueKnights());
  EXPECT_EQ(6, cp.valueBishops());
  EXPECT_EQ(10, cp.valueRooks());
  EXPECT_EQ(9, cp.valueQueens());
}

TEST(PieceCountTest, OutputOp) {
  PieceCount cp;
  ostringstream ss1;
  ss1 << cp;
  string s("{kings=1, queens=1, rooks=2, bishops=2, knights=2, pawns=8, total=16}");
  
  EXPECT_EQ(s, ss1.str()); 
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
