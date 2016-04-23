/////////////////////////////////////////////////////////////////////////////////////
/// @file tpiececode.cc
/// @author Omar A Serrano
/// @date 2016-01-09
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <string>
#include <sstream>

//
// zoor
//
#include "piececode.hh"
#include "piececount.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//
using std::string;
using std::ostringstream;

//
// using from zoor
//
using zoor::PieceCode;
using zoor::PieceCount;

//
// Test the default constructor yields a board with the default number of pieces.
//
TEST(PieceCount1, CtorValues)
{
  PieceCount cp;
  EXPECT_EQ(1, cp.kings()); 
  EXPECT_EQ(1, cp.queens()); 
  EXPECT_EQ(2, cp.rooks()); 
  EXPECT_EQ(2, cp.bishops()); 
  EXPECT_EQ(2, cp.knights()); 
  EXPECT_EQ(8, cp.pawns()); 
}

//
// Test PieceCount::clear().
//
TEST(PieceCount3, ClearFn)
{
  PieceCount cp;
  cp.clear();
  EXPECT_EQ(0, cp.kings());
  EXPECT_EQ(0, cp.queens());
  EXPECT_EQ(0, cp.rooks());
  EXPECT_EQ(0, cp.bishops());
  EXPECT_EQ(0, cp.knights());
  EXPECT_EQ(0, cp.pawns());
}

//
// Test equality and non-equality operators.
//
TEST(PieceCount7, EqualityOp)
{
  PieceCount cp1, cp2;
  EXPECT_TRUE(cp1 == cp2);
  EXPECT_FALSE(cp1 != cp2);

  cp2.setCount(PieceCode::PAWN, 5);
  EXPECT_FALSE(cp1 == cp2);
  EXPECT_TRUE(cp1 != cp2);
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
