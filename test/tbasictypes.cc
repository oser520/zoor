/////////////////////////////////////////////////////////////////////////////////////
/// @file tbasictypes.cc
/// @author Omar A Serrano
/// @date 2016-05-02
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <sstream>

//
// zoor
//
#include "basictypes.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace zoor {

//
// using from STL
//
using std::ostringstream;

//
// test output string for Piece
//
TEST(BasicTypes, OutputOpPiece)
{
  ostringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7;
  ss1 << Piece::NONE; 
  ss2 << Piece::P; 
  ss3 << Piece::N; 
  ss4 << Piece::B; 
  ss5 << Piece::R; 
  ss6 << Piece::Q; 
  ss7 << Piece::K; 
  
  EXPECT_STREQ("NONE", ss1.str().c_str()); 
  EXPECT_STREQ("PAWN", ss2.str().c_str()); 
  EXPECT_STREQ("KNIGHT", ss3.str().c_str()); 
  EXPECT_STREQ("BISHOP", ss4.str().c_str()); 
  EXPECT_STREQ("ROOK", ss5.str().c_str()); 
  EXPECT_STREQ("QUEEN", ss6.str().c_str()); 
  EXPECT_STREQ("KING", ss7.str().c_str()); 
}

//
// test output string for Color
//
TEST(BasicTypes, OutputOpColor)
{
  ostringstream ss1, ss2, ss3;
  ss1 << Color::NONE; 
  ss2 << Color::W; 
  ss3 << Color::B; 
  
  EXPECT_STREQ("NONE", ss1.str().c_str()); 
  EXPECT_STREQ("WHITE", ss2.str().c_str()); 
  EXPECT_STREQ("BLACK", ss3.str().c_str()); 
}

//
// test output string for PieceMask
//
TEST(BasicTypes, OutputOpPieceMask)
{
  ostringstream ss1, ss2;
  ss1 << PieceMask::PIECE;
  ss2 << PieceMask::COLOR;

  EXPECT_STREQ("0x7", ss1.str().c_str());
  EXPECT_STREQ("0x18", ss2.str().c_str());
}

//
// test logical OR operator between Color and Piece
//
TEST(BasicTypes, LogicOrOpPieceT)
{
  piece_t pcolor = static_cast<piece_t>(Color::NONE);
  piece_t pcode = static_cast<piece_t>(Piece::P);
  EXPECT_EQ(pcolor | pcode, Color::NONE | Piece::P);

  pcolor = static_cast<piece_t>(Color::W);
  pcode = static_cast<piece_t>(Piece::R);
  EXPECT_EQ(pcolor | pcode, Color::W | Piece::R);

  pcolor = static_cast<piece_t>(Color::B);
  pcode = static_cast<piece_t>(Piece::B);
  EXPECT_EQ(pcolor | pcode, Color::B | Piece::B);
}

//
// test logical NOT operator for Color.
//
TEST(BasicTypes, LogicOpNotColor)
{
  EXPECT_EQ(Color::NONE, ~Color::NONE);
  EXPECT_EQ(Color::B, ~Color::W);
  EXPECT_EQ(Color::W, ~Color::B);
}

//
// test getPiece
//
TEST(BasicTypes, getPiece)
{
  EXPECT_EQ(Piece::R, getPiece(Color::W|Piece::R));
  EXPECT_EQ(Piece::B, getPiece(Color::B|Piece::B));
  EXPECT_EQ(Piece::K, getPiece(Color::W|Piece::K));
  EXPECT_EQ(Piece::NONE, getPiece(0));
}

//
// test getColor
//
TEST(BasicTypes, getColor)
{
  EXPECT_EQ(Color::W, getColor(Color::W|Piece::R));
  EXPECT_EQ(Color::B, getColor(Color::B|Piece::B));
  EXPECT_EQ(Color::W, getColor(Color::W|Piece::K));
  EXPECT_EQ(Color::NONE, getColor(0));
}

//
// test isPawn
//
TEST(BasicTypes, isPawn)
{
  EXPECT_TRUE(isPawn(Piece::P));
  EXPECT_TRUE(isPawn(Color::W|Piece::P));
  EXPECT_FALSE(isPawn(Piece::R));
  EXPECT_FALSE(isPawn(Color::W|Piece::R));
}

//
// test isKnight
//
TEST(BasicTypes, isKnight)
{
  EXPECT_TRUE(isKnight(Piece::N));
  EXPECT_TRUE(isKnight(Color::W|Piece::N));
  EXPECT_FALSE(isKnight(Piece::R));
  EXPECT_FALSE(isKnight(Color::W|Piece::R));
}

//
// test isBishop
//
TEST(BasicTypes, isBishop)
{
  EXPECT_TRUE(isBishop(Piece::B));
  EXPECT_TRUE(isBishop(Color::W|Piece::B));
  EXPECT_FALSE(isBishop(Piece::R));
  EXPECT_FALSE(isBishop(Color::W|Piece::R));
}

//
// test isRook
//
TEST(BasicTypes, isRook)
{
  EXPECT_TRUE(isRook(Piece::R));
  EXPECT_TRUE(isRook(Color::W|Piece::R));
  EXPECT_FALSE(isRook(Piece::B));
  EXPECT_FALSE(isRook(Color::W|Piece::B));
}

//
// test isQueen
//
TEST(BasicTypes, isQueen)
{
  EXPECT_TRUE(isQueen(Piece::Q));
  EXPECT_TRUE(isQueen(Color::W|Piece::Q));
  EXPECT_FALSE(isQueen(Piece::B));
  EXPECT_FALSE(isQueen(Color::W|Piece::B));
}

//
// test isKing
//
TEST(BasicTypes, isKing)
{
  EXPECT_TRUE(isKing(Piece::K));
  EXPECT_TRUE(isKing(Color::W|Piece::K));
  EXPECT_FALSE(isKing(Piece::B));
  EXPECT_FALSE(isKing(Color::W|Piece::B));
}

//
// test notPiece
//
TEST(BasicTypes, notPiece)
{
  EXPECT_FALSE(notPiece(Piece::K));
  EXPECT_FALSE(notPiece(Color::W|Piece::P));
  EXPECT_TRUE(notPiece(Piece::NONE));
  EXPECT_TRUE(notPiece(0));
}

//
// test notColor
//
TEST(BasicTypes, notColor)
{
  EXPECT_FALSE(notColor(Color::W));
  EXPECT_FALSE(notColor(Color::W|Piece::P));
  EXPECT_TRUE(notColor(Color::NONE));
  EXPECT_TRUE(notColor(0));
}

//
// test isSame with piece argument
//
TEST(BasicTypes, isSamePiece)
{
  EXPECT_TRUE(isSame(Color::W|Piece::K, Piece::K));
  EXPECT_FALSE(isSame(Color::W|Piece::K, Piece::R));
}

//
// test isSame with color argument
//
TEST(BasicTypes, isSameColor)
{
  EXPECT_TRUE(isSame(Color::W|Piece::K, Color::W));
  EXPECT_FALSE(isSame(Color::W|Piece::K, Color::B));
}

} // namespace zoor
