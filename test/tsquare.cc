/////////////////////////////////////////////////////////////////////////////////////
//! @file tsquare.cc
//! @author Omar A Serrano
//! @date 2016-01-05
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <string>
#include <utility>

//
// zoor
//
#include "basictypes.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace zoor {

using std::string;

//
// Test for default ctor.
//
TEST(Square, DefaultCtor)
{
  Square s;
  EXPECT_EQ(0, s.row());
  EXPECT_EQ(0, s.column());
  EXPECT_EQ(Piece::NONE, s.piece());
  EXPECT_EQ(Color::NONE, s.color());
}

//
// Test for ctor with 2 parameters.
//
TEST(Square, Ctor2Param)
{
  Square s(3, 5);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(Piece::NONE, s.piece());
  EXPECT_EQ(Color::NONE, s.color());
}

//
// Test for ctor with 3 parameters.
//
TEST(Square, Ctor3Param)
{
  Square s(3, 5, Color::W|Piece::B);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(Piece::B, s.piece());
  EXPECT_EQ(Color::W, s.color());
}

//
// Test for ctor with 4 parameters.
//
TEST(Square, Ctor4Param)
{
  Square s(3, 5, Piece::B, Color::W);
  EXPECT_EQ(3, s.row());
  EXPECT_EQ(5, s.column());
  EXPECT_EQ(Piece::B, s.piece());
  EXPECT_EQ(Color::W, s.color());
}

//
// Test getters.
//
TEST(Square, Getters)
{
  Square s;
  s.piece(Piece::K).color(Color::W).row(5).column(7);
  EXPECT_EQ(Piece::K, s.piece());
  EXPECT_EQ(Color::W, s.color());
  EXPECT_EQ(5, s.row());
  EXPECT_EQ(7, s.column());
  EXPECT_EQ(Color::W|Piece::K, s.code());

  EXPECT_NE(Piece::B, s.piece());
  EXPECT_NE(Color::B, s.color());
  EXPECT_NE(1, s.row());
  EXPECT_NE(3, s.column());
  EXPECT_NE(Color::B|Piece::R, s.code());
}

//
// Test setters.
//
TEST(Square, Setters)
{
  Square s;
  s.piece(Piece::P).color(Color::B).row(5).column(7);
  auto p = s.location();

  EXPECT_EQ(Piece::P, s.piece());
  EXPECT_EQ(Color::B, s.color());
  EXPECT_EQ(5, s.row());
  EXPECT_EQ(7, s.column());
  EXPECT_EQ(5, p.first);
  EXPECT_EQ(7, p.second);

  s.location(2, 5);
  EXPECT_NE(5, s.row());
  EXPECT_NE(7, s.column());

  auto pcode = Color::W | Piece::Q;
  s.code(pcode);
  EXPECT_EQ(Piece::Q, s.piece());
  EXPECT_EQ(Color::W, s.color());
  EXPECT_EQ(pcode, s.code());
}

//
// Test bools.
//
TEST(Square, Bools) {
  Square s1(5, 7, Piece::K, Color::B);
  Square s2(5, 7, Piece::K, Color::B);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 != s2);

  s1.piece(Piece::K).color(Color::W).row(5).column(7);

  EXPECT_FALSE(s1 == s2);
  EXPECT_TRUE(s1 != s2);
}

//
// Unit tests for equality operators.
//
TEST(Square, EqualOp)
{
  Square s1, s2;
  EXPECT_EQ(s1, s2);

  s1.piece(Piece::K);
  EXPECT_NE(s1, s2);

  s1.piece(Piece::NONE);
  s2.color(Color::W);
  EXPECT_NE(s1, s2);

  s1.piece(Piece::R).color(Color::B).row(5);
  s2.piece(Piece::R).color(Color::B).row(3);
  EXPECT_NE(s1, s2);

  s2.row(5);
  EXPECT_EQ(s1, s2);

  s1.location(5, 7).piece(Piece::K).color(Color::B);
  s2.location(5, 7).piece(Piece::K).color(Color::B);

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 != s2);

  s1.color(Color::W);

  EXPECT_FALSE(s1 == s2);
  EXPECT_TRUE(s1 != s2);
}

//
// unit tests for toString
//
TEST(Square, ToString)
{
  Square sq1(5, 7, Piece::R, Color::W);
  Square sq2(3, 2, Piece::Q, Color::B);

  string s1("(ROOK, WHITE, 5, 7)");
  string s2("(QUEEN, BLACK, 3, 2)");

  EXPECT_EQ(s1, sq1.toString());
  EXPECT_EQ(s2, sq2.toString());
}

//
// unit tests for hashCode
//
TEST(Square, HashCode)
{
  Square sq1(5, 7, Piece::R, Color::W);
  Square sq2(3, 2, Piece::Q, Color::B);

  EXPECT_NE(sq1.hashCode(), sq2.hashCode());
}

} // namespace zoor
