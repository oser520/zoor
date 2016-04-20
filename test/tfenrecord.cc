/////////////////////////////////////////////////////////////////////////////////////
/// @file tfenrecord.cc
/// @author Omar A Serrano
/// @date 2016-04-20
/////////////////////////////////////////////////////////////////////////////////////

//
// STL headers
//
#include <memory>

//
// zoor headers
//
#include "board.hh"
#include "fenrecord.hh"

//
// gtest header
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//
using std::make_shared;

//
// using from zoor
//
using zoor::Board;
using zoor::FenRecord;

//
// Test FenRecord
//
TEST(FenRecord, CtorAndGetters)
{
  Board board;
  auto pb = make_shared<Board>();
  FenRecord fr(pb, 0, 0);

  EXPECT_EQ(board, *(fr.boardPtr()));
  EXPECT_EQ(0, fr.halfMove());
  EXPECT_EQ(0, fr.fullMove());
}

} // namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

