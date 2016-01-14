/**
 * @file tpiecemoves.cc
 * @author Omar A Serrano
 * @date 2016-01-12
 */

#include <sstream>
#include "piececode.hh"
#include "square.hh"
#include "piecemoves.hh"
#include "gtest/gtest.h"

namespace {

using std::ostringstream;
using zoor::PieceCode;
using zoor::PieceMoves;

/**
 * Test the values of the piece making the moves with default constructor.
 */
TEST(PieceMovesTest, DefaultCtor)
{
  PieceMoves pm;
  EXPECT_EQ(PieceCode::NONE, pm.piece());
  EXPECT_EQ(PieceColor::NONE, pm.color());
  EXPECT_EQ(static_cast<PieceMoves::size_type>(0), pm.size());
  EXPECT_TRUE(pm.empty());
}

/**
 * Test the values of the piece making the moves with 1-param constructor.
 */
TEST(PieceMovesTest, SquareParamCtor)
{
  Square sq(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  PieceMoves pm(sq);
  EXPECT_EQ(PieceCode::ROOK, pm.piece());
  EXPECT_EQ(PieceColor::BLACK, pm.color());
  EXPECT_EQ(1, pm.row());
  EXPECT_EQ(2, pm.column());
}

/**
 * Test the values of the piece making the moves with all-param constructor.
 */
TEST(PieceMovesTest, AllParamCtor)
{
  PieceMoves pm(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  EXPECT_EQ(PieceCode::ROOK, pm.piece());
  EXPECT_EQ(PieceColor::BLACK, pm.color());
  EXPECT_EQ(1, pm.row());
  EXPECT_EQ(2, pm.column());
}

/**
 * Test inserting and querying moves.
 */
TEST(PieceMovesTest, InsertMoves)
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

  int i = 1;
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
TEST(PieceMovesTest, EqualOp)
{
  PieceMoves pm1(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  PieceMoves pm2(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  EXPECT_TRUE(pm1 == pm2);

  pm1.pop_back();
  EXPECT_FALSE(pm1 == pm2);
}

/**
 * Test the output operator.
 */
TEST(PieceMovesTest, OutputOp) {
  PieceMoves pm1(1, 2, PieceCode::ROOK, PieceColor::BLACK);
  pm.push_back(Square(1,3, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(1,6, PieceCode::NONE, PieceColor::NONE));
  pm.push_back(Square(5,2, PieceCode::PAWN, PieceColor::WHITE));

  ostringstream ss1, ss2;
  ss1 << "(ROOK, BLACK, 1, 2, ("
      << "(NONE, NONE, 1, 3), ("
      << "(NONE, NONE, 1, 6), ("
      << "(PAWN, WHITE, 5, 2))";
  ss2 << pm;
  
  EXPECT_EQ(ss1.str(), ss2.str()); 
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
