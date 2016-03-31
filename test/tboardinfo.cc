/**
 * @file tboardinfo.cc
 * @author Omar A Serrano
 * @date 2016-03-29
 */

#include <string>
#include <sstream>
#include <functional>
#include "boardinfo.hh"
#include "gtest/gtest.h"

namespace {

using zoor::BoardInfo;

// test get
TEST(BoardInfo1, get)
{
  BoardInfo bi;
  const auto& bs = bi.get();
  EXPECT_EQ(10, bs.size());
  EXPECT_FALSE(bs.any());
}

// test rookA1 and rookA1On
TEST(BoardInfo2, rookA1)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.rookA1());
  EXPECT_TRUE(bi.rookA1On().rookA1());
}

// test rookH1 and rookH1On
TEST(BoardInfo3, rookH1)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.rookH1());
  EXPECT_TRUE(bi.rookH1On().rookH1());
}

// test wkMoved and wkMovedOn
TEST(BoardInfo4, wkMoved)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.wkMoved());
  EXPECT_TRUE(bi.wkMovedOn().wkMoved());
}

// test wkCheck and wkCheckSet
TEST(BoardInfo5, wkCheck)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.wkCheck());
  EXPECT_TRUE(bi.wkCheckSet(true).wkCheck());
  EXPECT_FALSE(bi.wkCheckSet(false).wkCheck());
}

// test wkMate and wkMateOn
TEST(BoardInfo6, wkMate)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.wkMate());
  EXPECT_TRUE(bi.wkMateOn().wkMate());
}

// test wkCastle and wkCastleLong
TEST(BoardInfo7, wkCastle)
{
  BoardInfo bi1;
  EXPECT_TRUE(bi1.wkCastle());
  EXPECT_FALSE(bi1.rookH1On().wkCastle());
  EXPECT_TRUE(bi1.wkCastleLong());
  EXPECT_FALSE(bi1.rookA1On().wkCastleLong());

  BoardInfo bi2;
  EXPECT_TRUE(bi2.wkCastle());
  EXPECT_TRUE(bi2.wkCastleLong());
  EXPECT_FALSE(bi2.wkCheckSet(true).wkCastle());
  EXPECT_FALSE(bi2.wkCastleLong());
  EXPECT_TRUE(bi2.wkCheckSet(false).wkCastle());
  EXPECT_TRUE(bi2.wkCastleLong());
  EXPECT_FALSE(bi2.wkMateOn().wkCastle());
  EXPECT_FALSE(bi2.wkCastleLong());
}

// test rookA8 and rookA8On
TEST(BoardInfo8, rookA8)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.rookA8());
  EXPECT_TRUE(bi.rookA8On().rookA8());
}

// test rookH8 and rookH8On
TEST(BoardInfo9, rookH8)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.rookH8());
  EXPECT_TRUE(bi.rookH8On().rookH8());
}

// test bkMoved and bkMovedOn
TEST(BoardInfo10, bkMoved)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.bkMoved());
  EXPECT_TRUE(bi.bkMovedOn().bkMoved());
}

// test bkCheck and bkCheckSet
TEST(BoardInfo11, bkCheck)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.bkCheck());
  EXPECT_TRUE(bi.bkCheckSet(true).bkCheck());
  EXPECT_FALSE(bi.bkCheckSet(false).bkCheck());
}

// test bkMate and bkMateOn
TEST(BoardInfo12, bkMate)
{
  BoardInfo bi;
  EXPECT_FALSE(bi.bkMate());
  EXPECT_TRUE(bi.bkMateOn().bkMate());
}

// test bkCastle and bkCastleLong
TEST(BoardInfo13, bkCastle)
{
  BoardInfo bi1;
  EXPECT_TRUE(bi1.bkCastle());
  EXPECT_FALSE(bi1.rookH8On().bkCastle());
  EXPECT_TRUE(bi1.bkCastleLong());
  EXPECT_FALSE(bi1.rookA8On().bkCastleLong());

  BoardInfo bi2;
  EXPECT_TRUE(bi2.bkCastle());
  EXPECT_TRUE(bi2.bkCastleLong());
  EXPECT_FALSE(bi2.bkCheckSet(true).bkCastle());
  EXPECT_FALSE(bi2.bkCastleLong());
  EXPECT_TRUE(bi2.bkCheckSet(false).bkCastle());
  EXPECT_TRUE(bi2.bkCastleLong());
  EXPECT_FALSE(bi2.bkMateOn().bkCastle());
  EXPECT_FALSE(bi2.bkCastleLong());
}

// test toString and output stream
TEST(BoardInfo14, toString)
{
  BoardInfo bi;
  std::ostringstream oss1, oss2;
  oss1 << bi.get();
  EXPECT_EQ(oss1.str(), bi.toString());

  bi.rookA1On().rookH8On().wkCheckSet(true).bkMovedOn();
  oss2 << bi.get();
  EXPECT_EQ(oss2.str(), bi.toString());
  EXPECT_NE(oss1.str(), bi.toString());
}

// test hashCode and hash<BoardInfo>
TEST(BoardInfo15, hashCode)
{
  BoardInfo bi1, bi2;
  bi1.rookA1On().rookH8On().wkCheckSet(true).bkMovedOn();
  bi2.rookA1On().rookH8On().wkCheckSet(true);
  EXPECT_NE(bi1.hashCode(), bi2.hashCode());
  EXPECT_EQ(bi1.hashCode(), std::hash<BoardInfo>()(bi1));

  bi2.bkMovedOn();
  EXPECT_EQ(bi1.hashCode(), bi2.hashCode());
}

// test operator== and operator!=
TEST(BoardInfo16, operatorEq)
{
  BoardInfo bi1, bi2;
  bi1.rookA1On().rookH8On().wkCheckSet(true).bkMovedOn();
  bi2.rookA1On().rookH8On().wkCheckSet(true);
  EXPECT_NE(bi1, bi2);

  bi2.bkMovedOn();
  EXPECT_EQ(bi1.hashCode(), bi2.hashCode());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
