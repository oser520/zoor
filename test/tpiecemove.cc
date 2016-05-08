/////////////////////////////////////////////////////////////////////////////////////
/// @file tpiecemoves.cc
/// @author Omar A Serrano
/// @date 2016-01-12
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <sstream>
#include <string>

//
// zoor
//
#include "basictypes.hh"
#include "piecemove.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using std::string;
using zoor::Piece;
using zoor::Color;
using zoor::PieceMove;
using zoor::Square;

//
// Test the values of the piece making the moves with default constructor.
//
TEST(PieceMove, DefaultCtor)
{
  PieceMove pm;

  EXPECT_EQ(Piece::NONE, pm.sPiece());
  EXPECT_EQ(Color::NONE, pm.sColor());
  EXPECT_EQ(0, pm.sRow());
  EXPECT_EQ(0, pm.sColumn());

  EXPECT_EQ(Piece::NONE, pm.dPiece());
  EXPECT_EQ(Color::NONE, pm.dColor());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  EXPECT_EQ(PieceCode::NONE, pm.xPiece());
  EXPECT_EQ(PieceColor::NONE, pm.xColor());
  EXPECT_EQ(0, pm.xRow());
  EXPECT_EQ(0, pm.xColumn());

  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// Test the values of the piece making the moves with 1-param constructor.
//
TEST(PieceMove, FourParamCtor)
{
  PieceMove pm(3, 5, Piece::R, Color::W);

  EXPECT_EQ(Piece::R, pm.sPiece());
  EXPECT_EQ(Color::W, pm.sColor());
  EXPECT_EQ(3, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());

  EXPECT_EQ(Piece::NONE, pm.dPiece());
  EXPECT_EQ(Color::NONE, pm.dColor());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  EXPECT_EQ(Piece::NONE, pm.xPiece());
  EXPECT_EQ(Color::NONE, pm.xColor());
  EXPECT_EQ(0, pm.xRow());
  EXPECT_EQ(0, pm.xColumn());

  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// Test the values of the piece making the moves with all-param constructor.
//
TEST(PieceMove, ThreeParamCtor)
{
  PieceMove pm(3, 5, Color::W|Piece::R);

  EXPECT_EQ(Piece::R, pm.sPiece());
  EXPECT_EQ(Color::W, pm.sColor());
  EXPECT_EQ(3, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());

  EXPECT_EQ(Piece::NONE, pm.dPiece());
  EXPECT_EQ(Color::NONE, pm.dColor());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  EXPECT_EQ(Piece::NONE, pm.xPiece());
  EXPECT_EQ(Color::NONE, pm.xColor());
  EXPECT_EQ(0, pm.xRow());
  EXPECT_EQ(0, pm.xColumn());

  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// Test the values of the piece making the moves with all-param constructor.
//
TEST(PieceMove, FiveParamCtor)
{
  PieceMove pm(3, 5, Color::W|Piece::R, 2, 6);

  EXPECT_EQ(Piece::R, pm.sPiece());
  EXPECT_EQ(Color::W, pm.sColor());
  EXPECT_EQ(3, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());

  EXPECT_EQ(Piece::NONE, pm.dPiece());
  EXPECT_EQ(Color::NONE, pm.dColor());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  EXPECT_EQ(Piece::NONE, pm.xPiece());
  EXPECT_EQ(Color::NONE, pm.xColor());
  EXPECT_EQ(2, pm.xRow());
  EXPECT_EQ(6, pm.xColumn());

  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// test sPiece()
//
TEST(PieceMove, SPiece)
{
  PieceMove pm;

  // 4 param sPiece
  pm.sPiece(1, 3, Piece::R, Color::W);
  EXPECT_EQ(1, pm.sRow());
  EXPECT_EQ(3, pm.sColumn());
  EXPECT_EQ(Piece::R, pm.sPiece());
  EXPECT_EQ(Color::W, pm.sColor());

  // 3 param sPiece
  pm.sPiece(2, 5, Color::B|Piece::K);
  EXPECT_EQ(2, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());
  EXPECT_EQ(Piece::K, pm.sPiece());
  EXPECT_EQ(Color::B, pm.sColor());

  // 2 param sPiece
  pm.sPiece(Piece::Q, Color::W);
  EXPECT_EQ(2, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());
  EXPECT_EQ(Piece::Q, pm.sPiece());
  EXPECT_EQ(Color::W, pm.sColor());

  // 1 param sPiece
  pm.sPiece(Color::B|Piece::P);
  EXPECT_EQ(2, pm.sRow());
  EXPECT_EQ(5, pm.sColumn());
  EXPECT_EQ(Piece::P, pm.sPiece());
  EXPECT_EQ(Color::B, pm.sColor());
}

//
// test dPiece()
//
TEST(PieceMove, DPiece)
{
  PieceMove pm;

  // 4 param dPiece
  pm.dPiece(1, 3, Piece::R, Color::W);
  EXPECT_EQ(1, pm.dRow());
  EXPECT_EQ(3, pm.dColumn());
  EXPECT_EQ(Piece::R, pm.dPiece());
  EXPECT_EQ(Color::W, pm.dColor());

  // 3 param dPiece
  pm.dPiece(2, 5, Color::B|Piece::K);
  EXPECT_EQ(2, pm.dRow());
  EXPECT_EQ(5, pm.dColumn());
  EXPECT_EQ(Piece::K, pm.dPiece());
  EXPECT_EQ(Color::B, pm.dColor());

  // 2 param dPiece
  pm.dPiece(Piece::Q, Color::W);
  EXPECT_EQ(2, pm.dRow());
  EXPECT_EQ(5, pm.dColumn());
  EXPECT_EQ(Piece::Q, pm.dPiece());
  EXPECT_EQ(Color::W, pm.dColor());

  // 1 param dPiece
  pm.dPiece(Color::B|Piece::P);
  EXPECT_EQ(2, pm.dRow());
  EXPECT_EQ(5, pm.dColumn());
  EXPECT_EQ(Piece::P, pm.dPiece());
  EXPECT_EQ(Color::B, pm.dColor());
}

//
// test xPromo()
//
TEST(PieceMove, XPiece)
{
  PieceMove pm;

  // 4 param xPiece
  pm.xPiece(1, 3, Piece::R, Color::W);
  EXPECT_EQ(1, pm.xRow());
  EXPECT_EQ(3, pm.xColumn());
  EXPECT_EQ(Piece::R, pm.xPiece());
  EXPECT_EQ(Color::W, pm.xColor());

  // 3 param xPiece
  pm.xPiece(2, 5, Color::B|Piece::K);
  EXPECT_EQ(2, pm.xRow());
  EXPECT_EQ(5, pm.xColumn());
  EXPECT_EQ(Piece::K, pm.xPiece());
  EXPECT_EQ(Color::B, pm.xColor());

  // 2 param xPiece
  pm.xPiece(Piece::Q, Color::W);
  EXPECT_EQ(2, pm.xRow());
  EXPECT_EQ(5, pm.xColumn());
  EXPECT_EQ(Piece::Q, pm.xPiece());
  EXPECT_EQ(Color::W, pm.xColor());

  // 1 param xPiece
  pm.xPiece(Color::B|Piece::P);
  EXPECT_EQ(2, pm.xRow());
  EXPECT_EQ(5, pm.xColumn());
  EXPECT_EQ(Piece::P, pm.xPiece());
  EXPECT_EQ(Color::B, pm.xColor());
}

//
// test isCapture()
//
TEST(PieceMove, IsCapture)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isCapture());

  pm.xPiece(2, 5, Color::B|Piece::K);
  EXPECT_TRUE(pm.isCapture());
}

//
// test isPromo()
//
TEST(PieceMove, IsPromo)
{
  PieceMove pm(6, 2, Color::W|Piece::P, 7, 2);
  EXPECT_FALSE(pm.isPromo());

  pm.dPiece(Piece::N);
  EXPECT_TRUE(pm.isPromo());
}

//
// test dRow()
//
TEST(PieceMove, DRow)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  pm.dRow(2);
  EXPECT_EQ(2, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());
}

//
// test dColumn()
//
TEST(PieceMove, DColumn)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  pm.dColumn(2);
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(2, pm.dColumn());
}

//
// test dLocation()
//
TEST(PieceMove, DLocation)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());

  pm.dLocation(2, 3);
  EXPECT_EQ(2, pm.dRow());
  EXPECT_EQ(3, pm.dColumn());
}

//
// test isMate
//
TEST(PieceMove, IsMate)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isMate());

  pm.xPiece(Piece::K, Color::B);
  EXPECT_TRUE(pm.isMate());
}

//
// test isCatle() for white
//
TEST(PieceMove, WhiteCastling)
{
  PieceMove pm;

  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());

  pm.sPiece(0, 4, Piece::K, Color::W);
  pm.dPiece(0, 6, Piece::K, Color::W);
  pm.xPiece(0, 7, Piece::R, Color::W);

  EXPECT_TRUE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// test isCastle() for black
//
TEST(PieceMove, BlackCastling)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());

  pm.sPiece(7, 4, Piece::K, Color::B);
  pm.dPiece(7, 6, Piece::K, Color::B);
  pm.xPiece(7, 7, Piece::R, Color::B);

  EXPECT_TRUE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());
}

//
// test isCatleLong() for white
//
TEST(PieceMove, WhiteCastlingLong)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());

  pm.sPiece(0, 4, Piece::K, Color::W);
  pm.dPiece(0, 2, Piece::K, Color::W);
  pm.xPiece(0, 0, Piece::R, Color::W);

  EXPECT_FALSE(pm.isCastle());
  EXPECT_TRUE(pm.isCastleLong());
}

//
// test isCastleLong() for black
//
TEST(PieceMove, BlackCastlingLong)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isCastle());
  EXPECT_FALSE(pm.isCastleLong());

  pm.sPiece(7, 4, Piece::K, Color::B);
  pm.dPiece(7, 2, Piece::K, Color::B);
  pm.xPiece(7, 0, Piece::R, Color::B);

  EXPECT_FALSE(pm.isCastle());
  EXPECT_TRUE(pm.isCastleLong());
}

//
// test isEnPassant()
//
TEST(PieceMove, IsEnPassant)
{
  PieceMove pm(4, 5, Color::W|Piece::P, 5, 6);
  pm.xPiece(4, 6, Piece::P, Color::B);
  EXPECT_TRUE(pm.isEnPassant());

  PieceMove pm1(3, 5, Color::W|Piece::R, 6, 5);
  pm1.xPiece(Piece::P, Color::B);
  EXPECT_FALSE(pm1.isEnPassant());
}

//
// test toString
//
TEST(PieceMove, ToString)
{
  PieceMove pm(3, 5, Color::W|Piece::R, 6, 5);
  pm.xPiece(Piece::P, Color::B);

  string s1("((ROOK, WHITE, 3, 5), (NONE, NONE, 6, 5), (PAWN, BLACK, 0, 0))");

  EXPECT_EQ(s1, pm.toString());
}

//
// test hashCode
//
TEST(PieceMove, HashCode)
{
  PieceMove pm(3, 5, Color::W|Piece::R, 6, 5);
  pm.xPiece(Piece::P, Color::B);
  PieceMove pm1(3, 5, Color::W|Piece::R, 6, 5);

  EXPECT_NE(pm.hashCode(), pm1.hashCode());
}

//
// test the equality operators
//
TEST(PieceMove, EqualOp)
{
  PieceMove pm1(1, 2, Color::B|Piece::R, 3, 3);
  pm1.xPiece(3, 3, Piece::P, Color::W);
  PieceMove pm2(pm1);

  EXPECT_TRUE(pm1 == pm2);
  EXPECT_FALSE(pm1 != pm2);

  pm2.dLocation(5, 5);
  EXPECT_TRUE(pm1 != pm2);
  EXPECT_FALSE(pm1 == pm2);
}

//
// test the output operator
//
TEST(PieceMove, OutputOp)
{
  PieceMove pm(1, 2, Piece::R, Color::B);
  pm.xPiece(3, 3, Piece::P, Color::W);
  pm.dLocation(3, 3);

  ostringstream ss1, ss2;
  ss1 << "((ROOK, BLACK, 1, 2),"
      << " (NONE, NONE, 3, 3),"
      << " (PAWN, WHITE, 3, 3))";
  ss2 << pm;
  
  EXPECT_EQ(ss1.str(), ss2.str()); 
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
