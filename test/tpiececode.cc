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
using namespace zoor;

/**
 * Test PieceCode output string.
 */
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

/**
 * Test PieceColor output string.
 */
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

/**
 * Test PieceValue on cast.
 */
TEST(PieceValueTest, PieceValue)
{
  EXPECT_EQ(0, static_cast<piecevalue_t>(PieceValue::NONE));
  EXPECT_EQ(1, static_cast<piecevalue_t>(PieceValue::PAWN));
  EXPECT_EQ(3, static_cast<piecevalue_t>(PieceValue::KNIGHT));
  EXPECT_EQ(3, static_cast<piecevalue_t>(PieceValue::BISHOP));
  EXPECT_EQ(5, static_cast<piecevalue_t>(PieceValue::ROOK));
  EXPECT_EQ(9, static_cast<piecevalue_t>(PieceValue::QUEEN));
  EXPECT_EQ(0x7fff, static_cast<piecevalue_t>(PieceValue::KING));
}

/**
 * Test PieceMask on output.
 */
TEST(PieceMaskTest, OutputOp)
{
  ostringstream ss1, ss2;
  ss1 << PieceMask::PIECE;
  ss2 << PieceMask::COLOR;

  EXPECT_STREQ("0x7", ss1.str().c_str());
  EXPECT_STREQ("0x18", ss2.str().c_str());
}

/**
 * Test logical and operator for color and piece.
 */
TEST(PieceAndColor, LogicOpAnd)
{
  piececode_t pcolor = static_cast<piececode_t>(PieceColor::NONE);
  piececode_t pcode = static_cast<piececode_t>(PieceCode::PAWN);
  EXPECT_EQ(pcolor | pcode, PieceColor::NONE | PieceCode::PAWN);

  pcolor = static_cast<piececode_t>(PieceColor::WHITE);
  pcode = static_cast<piececode_t>(PieceCode::ROOK);
  EXPECT_EQ(pcolor | pcode, PieceColor::WHITE | PieceCode::ROOK);

  pcolor = static_cast<piececode_t>(PieceColor::BLACK);
  pcode = static_cast<piececode_t>(PieceCode::BISHOP);
  EXPECT_EQ(pcolor | pcode, PieceColor::BLACK | PieceCode::BISHOP);
}

/**
 * Test logical not operator for color.
 */
TEST(PieceColorNot, LogicOpNot)
{
  EXPECT_EQ(PieceColor::NONE, ~PieceColor::NONE);
  EXPECT_EQ(PieceColor::BLACK, ~PieceColor::WHITE);
  EXPECT_EQ(PieceColor::WHITE, ~PieceColor::BLACK);
}

/**
 * Test getPieceCode and getPieceColor.
 */
TEST(PieceCodeFunc, GetCodeFunc)
{
  auto code = PieceColor::WHITE | PieceCode::ROOK;
  EXPECT_EQ(PieceColor::WHITE, getPieceColor(code));
  EXPECT_EQ(PieceCode::ROOK, getPieceCode(code));

  code = PieceColor::BLACK | PieceCode::BISHOP;
  EXPECT_EQ(PieceColor::BLACK, getPieceColor(code));
  EXPECT_EQ(PieceCode::BISHOP, getPieceCode(code));
}

// test isPawn
TEST(isPawnTest, isPawn)
{
  auto piece = PieceCode::PAWN;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isPawn(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isPawn(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isRook(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isRook(code));
  EXPECT_FALSE(isBlack(code));
}

// test isKnight
TEST(isKnightTest, isKnight)
{
  auto piece = PieceCode::KNIGHT;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isKnight(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isKnight(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isRook(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isRook(code));
  EXPECT_FALSE(isBlack(code));
}

// test isBishop
TEST(isBishopTest, isBishop)
{
  auto piece = PieceCode::BISHOP;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isBishop(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isBishop(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isRook(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isRook(code));
  EXPECT_FALSE(isBlack(code));
}

// test isRook
TEST(isRookTest, isRook)
{
  auto piece = PieceCode::ROOK;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isRook(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isRook(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isQueen(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isQueen(code));
  EXPECT_FALSE(isBlack(code));
}

// test isQueen
TEST(isQueenTest, isQueen)
{
  auto piece = PieceCode::QUEEN;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isQueen(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isQueen(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isRook(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isRook(code));
  EXPECT_FALSE(isBlack(code));
}

// test isKing
TEST(isKingTest, isKing)
{
  auto piece = PieceCode::KING;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isKing(piece));
  EXPECT_TRUE(isWhite(color));
  EXPECT_TRUE(isKing(code));
  EXPECT_TRUE(isWhite(code));

  EXPECT_FALSE(isRook(piece));
  EXPECT_FALSE(isBlack(color));
  EXPECT_FALSE(isRook(code));
  EXPECT_FALSE(isBlack(code));
}

// test isPieceNone
TEST(isPieceNoneTest, isPieceNone)
{
  auto piece = PieceCode::KING;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_FALSE(isPieceNone(piece));
  EXPECT_FALSE(isPieceNone(code));

  piece = PieceCode::NONE;
  code = color | piece;

  EXPECT_TRUE(isPieceNone(piece));
  EXPECT_TRUE(isPieceNone(code));
}

// test isColorNone
TEST(isColorNoneTest, isColorNone)
{
  auto piece = PieceCode::KING;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_FALSE(isColorNone(color));
  EXPECT_FALSE(isColorNone(code));

  color = PieceColor::NONE;
  code = color | piece;

  EXPECT_TRUE(isColorNone(color));
  EXPECT_TRUE(isColorNone(code));
}

// test isSamePiece
TEST(isSamePieceTest, isSamePiece)
{
  auto piece = PieceCode::KING;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isSamePiece(code, piece));
  EXPECT_TRUE(isSamePiece(code, piece));

  piece = PieceCode::ROOK;

  EXPECT_FALSE(isSamePiece(code, piece));
  EXPECT_FALSE(isSamePiece(code, piece));
}

// test isSameColor
TEST(isSameColorTest, isSameColor)
{
  auto piece = PieceCode::KING;
  auto color = PieceColor::WHITE;
  auto code = color | piece;

  EXPECT_TRUE(isSameColor(code, color));
  EXPECT_TRUE(isSameColor(code, color));

  color = PieceColor::BLACK;

  EXPECT_FALSE(isSameColor(code, color));
  EXPECT_FALSE(isSameColor(code, color));
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
