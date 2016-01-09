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

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
