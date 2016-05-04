/////////////////////////////////////////////////////////////////////////////////////
/// @file tbasicboard.cc
/// @author Omar A Serrano
/// @date 2016-05-03
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <sstream>

//
// zoor
//
#include "basictypes.hh"
#include "basictboard.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//

//
// access all of zoor
//
using namespace zoor;

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

