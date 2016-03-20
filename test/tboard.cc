/**
 * @file tboard.cc
 * @author Omar A Serrano
 * @date 2016-03-19
 */

#include <sstream>
#include "piececode.hh"
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using namespace zoor;

/**
 * Test Board default ctor
 */
TEST(Board, Ctor)
{
}


} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

