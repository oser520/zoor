/**
 * @file tpiecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-12
 */

// TODO: add unit tests for PieceMove

#include <sstream>
#include "piececode.hh"
#include "square.hh"
#include "piecemoves.hh"
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using zoor::PieceCode;
using zoor::PieceColor;
using zoor::PieceMove;
using zoor::Square;

/**
 * Test the values of the piece making the moves with default constructor.
 */
TEST(PieceMove1, DefaultCtor)
{
  PieceMove pm;
  auto sq = pm.fromSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());

  sq = pm.captureSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());

  sq = pm.promoSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
}

/**
 * Test the values of the piece making the moves with 1-param constructor.
 */
TEST(PieceMove2, FourParamCtor)
{
  PieceMove pm(3, 5, PieceCode::ROOK, PieceColor::WHITE);
  auto sq = pm.fromSquare();
  EXPECT_EQ(PieceCode::ROOK, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());
  EXPECT_EQ(3, sq.row());
  EXPECT_EQ(5, sq.column());

  sq = pm.captureSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());

  sq = pm.promoSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
}

/**
 * Test the values of the piece making the moves with all-param constructor.
 */
TEST(PieceMove3, ThreeParamCtor)
{
  PieceMove pm(3, 5, PieceColor::WHITE | PieceCode::ROOK);
  auto sq = pm.fromSquare();
  EXPECT_EQ(PieceCode::ROOK, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());
  EXPECT_EQ(3, sq.row());
  EXPECT_EQ(5, sq.column());

  sq = pm.captureSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());

  sq = pm.promoSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
}

/**
 * Test the values of the piece making the moves with all-param constructor.
 */
TEST(PieceMove4, FiveParamCtor)
{
  auto pcode = PieceColor::WHITE | PieceCode::ROOK;
  PieceMove pm(3, 5, pcode, 2, 6);

  auto sq = pm.fromSquare();
  EXPECT_EQ(PieceCode::ROOK, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());
  EXPECT_EQ(3, sq.row());
  EXPECT_EQ(5, sq.column());

  sq = pm.captureSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());

  sq = pm.promoSquare();
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());
  EXPECT_EQ(2, sq.row());
  EXPECT_EQ(6, sq.column());
}

// test fromRow and fromColumn
TEST(PieceMove5, fromRowColumn)
{
  auto pcode = PieceColor::WHITE | PieceCode::ROOK;
  PieceMove pm(3, 5, pcode, 2, 6);

  EXPECT_EQ(3, pm.fromRow());
  EXPECT_EQ(5, pm.fromColumn());
}

// test toRow and toColumn
TEST(PieceMove6, toRowColumn)
{
  auto pcode = PieceColor::WHITE | PieceCode::ROOK;
  PieceMove pm(3, 5, pcode, 2, 6);

  EXPECT_EQ(2, pm.toRow());
  EXPECT_EQ(6, pm.toColumn());
}

// test setPiece
TEST(PieceMove7, setPiece)
{
  PieceMove pm;

  // 4 param setPiece
  pm.setPiece(1, 3, PieceCode::ROOK, PieceColor::WHITE);
  EXPECT_EQ(1, pm.fromRow());
  EXPECT_EQ(3, pm.fromColumn());
  EXPECT_EQ(PieceCode::ROOK, pm.fromPiece());
  EXPECT_EQ(PieceColor::WHITE, pm.fromColor());

  // 3 param setPiece
  pm.setPiece(2, 5, PieceColor::BLACK | PieceCode::KNIGHT);
  EXPECT_EQ(2, pm.fromRow());
  EXPECT_EQ(5, pm.fromColumn());
  EXPECT_EQ(PieceCode::KNIGHT, pm.fromPiece());
  EXPECT_EQ(PieceColor::BLACK, pm.fromColor());

  // 2 param setPiece
  pm.setPiece(PieceCode::QUEEN, PieceColor::WHITE);
  EXPECT_EQ(2, pm.fromRow());
  EXPECT_EQ(5, pm.fromColumn());
  EXPECT_EQ(PieceCode::QUEEN, pm.fromPiece());
  EXPECT_EQ(PieceColor::WHITE, pm.fromColor());

  // 1 param setPiece
  pm.setPiece(PieceCode::BLACK | PieceCode::PAWN);
  EXPECT_EQ(2, pm.fromRow());
  EXPECT_EQ(5, pm.fromColumn());
  EXPECT_EQ(PieceCode::PAWN, pm.fromPiece());
  EXPECT_EQ(PieceColor::BLACK, pm.fromColor());
}

// test setCapture
TEST(PieceMove8, setCapture)
{
  PieceMove pm;

  // 4 param setCapture
  pm.setCapture(1, 3, PieceCode::ROOK, PieceColor::WHITE);
  EXPECT_EQ(1, pm.captureRow());
  EXPECT_EQ(3, pm.captureColumn());
  EXPECT_EQ(PieceCode::ROOK, pm.capturePiece());
  EXPECT_EQ(PieceColor::WHITE, pm.captureColor());

  // 3 param setCapture
  pm.setCapture(2, 5, PieceColor::BLACK | PieceCode::KNIGHT);
  EXPECT_EQ(2, pm.captureRow());
  EXPECT_EQ(5, pm.captureColumn());
  EXPECT_EQ(PieceCode::KNIGHT, pm.capturePiece());
  EXPECT_EQ(PieceColor::BLACK, pm.captureColor());

  // 2 param setCapture
  pm.setCapture(PieceCode::QUEEN, PieceColor::WHITE);
  EXPECT_EQ(2, pm.captureRow());
  EXPECT_EQ(5, pm.captureColumn());
  EXPECT_EQ(PieceCode::QUEEN, pm.capturePiece());
  EXPECT_EQ(PieceColor::WHITE, pm.captureColor());

  // 1 param setCapture
  pm.setCapture(PieceCode::BLACK | PieceCode::PAWN);
  EXPECT_EQ(2, pm.captureRow());
  EXPECT_EQ(5, pm.captureColumn());
  EXPECT_EQ(PieceCode::PAWN, pm.capturePiece());
  EXPECT_EQ(PieceColor::BLACK, pm.captureColor());
}

// test setPromo
TEST(PieceMove9, setPromo)
{
  PieceMove pm;

  // 4 param setPromo
  pm.setPromo(1, 3, PieceCode::ROOK, PieceColor::WHITE);
  EXPECT_EQ(1, pm.toRow());
  EXPECT_EQ(3, pm.toColumn());
  EXPECT_EQ(PieceCode::ROOK, pm.promoPiece());
  EXPECT_EQ(PieceColor::WHITE, pm.promoColor());

  // 3 param setPromo
  pm.setPromo(2, 5, PieceColor::BLACK | PieceCode::KNIGHT);
  EXPECT_EQ(2, pm.toRow());
  EXPECT_EQ(5, pm.toColumn());
  EXPECT_EQ(PieceCode::KNIGHT, pm.promoPiece());
  EXPECT_EQ(PieceColor::BLACK, pm.promoColor());

  // 2 param setPromo
  pm.setPromo(PieceCode::QUEEN, PieceColor::WHITE);
  EXPECT_EQ(2, pm.toRow());
  EXPECT_EQ(5, pm.toColumn());
  EXPECT_EQ(PieceCode::QUEEN, pm.promoPiece());
  EXPECT_EQ(PieceColor::WHITE, pm.promoColor());

  // 1 param setPromo
  pm.setPromo(PieceCode::BLACK | PieceCode::PAWN);
  EXPECT_EQ(2, pm.toRow());
  EXPECT_EQ(5, pm.toColumn());
  EXPECT_EQ(PieceCode::PAWN, pm.promoPiece());
  EXPECT_EQ(PieceColor::BLACK, pm.promoColor());
}

// test isCapture
TEST(PieceMove10, isCapture)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isCapture());

  pm.setCapture(2, 5, PieceColor::BLACK | PieceCode::KNIGHT);
  EXPECT_TRUE(pm.isCapture());
}

// test isPromo
TEST(PieceMove11, isPromo)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isPromo());

  pm.setPromo(2, 5, PieceColor::BLACK | PieceCode::KNIGHT);
  EXPECT_TRUE(pm.isPromo());
}

// test setToRow
TEST(PieceMove12, setToRow)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.fromRow());
  EXPECT_EQ(0, pm.fromColumn());

  pm.setToRow(2);
  EXPECT_EQ(2, pm.fromRow());
  EXPECT_EQ(0, pm.fromColumn());
}

// test setToColumn
TEST(PieceMove13, setToColumn)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.fromRow());
  EXPECT_EQ(0, pm.fromColumn());

  pm.setToColumn(2);
  EXPECT_EQ(0, pm.fromRow());
  EXPECT_EQ(2, pm.fromColumn());
}

// test setGoTo
TEST(PieceMove14, setGoTo)
{
  PieceMove pm;
  EXPECT_EQ(0, pm.fromRow());
  EXPECT_EQ(0, pm.fromColumn());

  pm.setGoTo(2, 3);
  EXPECT_EQ(2, pm.fromRow());
  EXPECT_EQ(3, pm.fromColumn());
}

// test isMate
TEST(PieceMove15, isMate)
{
  PieceMove pm;
  EXPECT_FALSE(pm.isMate());

  pm.setCapture(PieceCode::KING, PieceColor::BLACK);
  EXPECT_TRUE(pm.isMate());
}

// test the equality operators
TEST(PieceMove16, EqualOp) {
  auto code = PieceColor::BLACK | PieceCode::ROOK;
  PieceMove pm1(1, 2, code, 3, 3);
  pm.setCapture(3, 3, PieceCode::PAWN, PieceColor::WHITE);
  PiecedMove pm2(pm1);

  EXPECT_TRUE(pm1 == pm2);
  EXPECT_FALSE(pm1 != pm2);

  pm2.setGoTo(5, 5);
  EXPECT_TRUE(pm1 != pm2);
  EXPECT_FALSE(pm1 == pm2);
}

// test the output operator
TEST(PieceMove16, OutputOp) {
  PieceMoves pm(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.setCapture(3, 3, PieceCode::PAWN, PieceColor::WHITE);
  pm.setGoTo(3, 3);

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
