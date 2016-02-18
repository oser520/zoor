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

// test fromRow
TEST(PieceMove5, fromRow)
{
  auto pcode = PieceColor::WHITE | PieceCode::ROOK;
  PieceMove pm(3, 5, pcode, 2, 6);

  EXPECT_EQ(3, pm.fromRow());
  EXPECT_EQ(5, pm.fromColumn());
}

/**
 * Test inserting and querying moves.
 */
TEST(PieceMove4, InsertMoves)
{
  PieceMoves pm(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  EXPECT_FALSE(pm.empty());
  EXPECT_EQ(3, pm.size());

  Square sq = pm.front();
  EXPECT_EQ(1, sq.row());
  EXPECT_EQ(3, sq.column());
  EXPECT_EQ(PieceCode::NONE, sq.piece());
  EXPECT_EQ(PieceColor::NONE, sq.color());

  sq = pm.back();
  EXPECT_EQ(5, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(PieceCode::PAWN, sq.piece());
  EXPECT_EQ(PieceColor::WHITE, sq.color());

  EXPECT_FALSE(pm.pop_back().empty());
  EXPECT_EQ(2, pm.size());

  int i = 0;
  auto it = pm.begin();
  while (it != pm.end())
    ++i, ++it;
  EXPECT_EQ(2, i); 

  pm.clear();
  EXPECT_TRUE(pm.empty());
}

/**
 * Test operator==.
 */
TEST(PieceMove5, EqualOp)
{
  PieceMoves pm1(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm1.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm1.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm1.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  PieceMoves pm2(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm2.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm2.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm2.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  EXPECT_TRUE(pm1 == pm2);

  pm1.pop_back();
  EXPECT_FALSE(pm1 == pm2);
}

/**
 * Test the output operator.
 */
TEST(PieceMove6, OutputOp) {
  PieceMoves pm(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  ostringstream ss1, ss2;
  ss1 << "((ROOK, BLACK, 1, 2), ("
      << "(NONE, NONE, 1, 3), "
      << "(NONE, NONE, 1, 6), "
      << "(PAWN, WHITE, 5, 2)))";
  ss2 << pm;
  
  EXPECT_EQ(ss1.str(), ss2.str()); 
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
