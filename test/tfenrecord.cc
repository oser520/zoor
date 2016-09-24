/////////////////////////////////////////////////////////////////////////////////////
//! @file tfenrecord.cc
//! @author Omar A Serrano
//! @date 2016-04-20
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

namespace zoor {

//
// using from STL
//
using std::make_shared;

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

} // namespace zoor
