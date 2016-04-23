/////////////////////////////////////////////////////////////////////////////////////
/// @file tiofen.cc
/// @author Omar A Serrano
/// @date 2016-04-21
/////////////////////////////////////////////////////////////////////////////////////

//
// zoor headers
//
#include "board.hh"
#include "fennotation.hh"

//
// gtest header
//
#include "gtest/gtest.h"

namespace {

//
// using from zoor
//
using zoor::Board;
using zoor::readFen;

//
// Test FenRecord
//
TEST(IOFen1, defaultBoard)
{
  Board board;
  auto fenList = readFen("fen/init.fen");

  EXPECT_EQ(1, fenList.size());

  auto fenrec = fenList.front();
  EXPECT_EQ(0, fenrec.halfMove());
  EXPECT_EQ(1, fenrec.fullMove());
  EXPECT_EQ(board, *fenrec.boardPtr());
}

} // namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
