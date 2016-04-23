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
TEST(PieceCount1, DefaultCtor)
{
  PieceCount cp;
  EXPECT_EQ(0, cp.wKing());
  EXPECT_EQ(0, cp.wQueen());
  EXPECT_EQ(0, cp.wRook());
  EXPECT_EQ(0, cp.wBishop());
  EXPECT_EQ(0, cp.wKnight());
  EXPECT_EQ(0, cp.wPawn());
  EXPECT_EQ(0, cp.white());
  EXPECT_EQ(0, cp.white());

  EXPECT_EQ(0, cp.bKing());
  EXPECT_EQ(0, cp.bQueen());
  EXPECT_EQ(0, cp.bRook());
  EXPECT_EQ(0, cp.bBishop());
  EXPECT_EQ(0, cp.bKnight());
  EXPECT_EQ(0, cp.bPawn());
  EXPECT_EQ(0, cp.black());

  EXPECT_TRUE(cp.good());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
