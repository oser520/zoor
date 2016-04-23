/////////////////////////////////////////////////////////////////////////////////////
/// @file tpiececode.cc
/// @author Omar A Serrano
/// @date 2016-01-09
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <string>
#include <sstream>
#include <vector>

//
// zoor
//
#include "board.hh"
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//
using std::ostringstream;
using std::string;
using std::vector;

//
// using from zoor
//
using zoor::Board;
using zoor::PieceCode;
using zoor::PieceColor;
using zoor::PieceCount;
using zoor::Square;
using zoor::piececode_t;

//
// Test the default ctor
//
TEST(PieceCount1, DefaultCtor)
{
  PieceCount cp;
  EXPECT_EQ(0, cp.wKing());
  EXPECT_EQ(0, cp.wQueen());
  EXPECT_EQ(0, cp.wRook());
  EXPECT_EQ(0, cp.wBishop());
  EXPECT_EQ(0, cp.wKnight());
  EXPECT_EQ(0, cp.wPawn());
  EXPECT_EQ(0, cp.white());
  EXPECT_EQ(0, cp.white());

  EXPECT_EQ(0, cp.bKing());
  EXPECT_EQ(0, cp.bQueen());
  EXPECT_EQ(0, cp.bRook());
  EXPECT_EQ(0, cp.bBishop());
  EXPECT_EQ(0, cp.bKnight());
  EXPECT_EQ(0, cp.bPawn());
  EXPECT_EQ(0, cp.black());

  EXPECT_TRUE(cp.good());
}

//
// Test the ctor with vector of squares
//
TEST(PieceCount2, SquareListCtor)
{
  vector<Square> sqList;

  // add white pawns
  auto wpawn = PieceColor::WHITE | PieceCode::PAWN;
  sqList.emplace_back(1, 0, wpawn);
  sqList.emplace_back(1, 1, wpawn);
  sqList.emplace_back(1, 2, wpawn);
  sqList.emplace_back(1, 3, wpawn);
  sqList.emplace_back(1, 4, wpawn);
  sqList.emplace_back(1, 5, wpawn);

  // add white knights
  auto wknight = PieceColor::WHITE | PieceCode::KNIGHT;
  sqList.emplace_back(0, 1, wknight);
  sqList.emplace_back(0, 6, wknight);

  // add white bishops
  auto wbishop = PieceColor::WHITE | PieceCode::BISHOP;
  sqList.emplace_back(0, 2, wbishop);
  sqList.emplace_back(0, 5, wbishop);

  // add white rook
  auto wrook = PieceColor::WHITE | PieceCode::ROOK;
  sqList.emplace_back(0, 0, wrook);
  sqList.emplace_back(0, 7, wrook);

  // add white queen
  auto wqueen = PieceColor::WHITE | PieceCode::QUEEN;
  sqList.emplace_back(0, 3, wqueen);

  // add white king
  auto wking = PieceColor::WHITE | PieceCode::KING;
  sqList.emplace_back(0, 4, wking);

  // add black pawns
  auto bpawn = PieceColor::BLACK | PieceCode::PAWN;
  sqList.emplace_back(6, 0, bpawn);
  sqList.emplace_back(6, 1, bpawn);
  sqList.emplace_back(6, 2, bpawn);
  sqList.emplace_back(6, 3, bpawn);
  sqList.emplace_back(6, 4, bpawn);
  sqList.emplace_back(6, 5, bpawn);

  // add black knights
  auto bknight = PieceColor::BLACK | PieceCode::KNIGHT;
  sqList.emplace_back(7, 1, bknight);
  sqList.emplace_back(7, 6, bknight);

  // add black bishops
  auto bbishop = PieceColor::BLACK | PieceCode::BISHOP;
  sqList.emplace_back(7, 2, bbishop);
  sqList.emplace_back(7, 5, bbishop);

  // add black rook
  auto brook = PieceColor::BLACK | PieceCode::ROOK;
  sqList.emplace_back(7, 0, brook);
  sqList.emplace_back(7, 7, brook);

  // add black queen
  auto bqueen = PieceColor::BLACK | PieceCode::QUEEN;
  sqList.emplace_back(7, 3, bqueen);

  // add black king
  auto bking = PieceColor::BLACK | PieceCode::KING;
  sqList.emplace_back(7, 4, bking);

  PieceCount pc(sqList);

  EXPECT_EQ(1, pc.wKing());
  EXPECT_EQ(1, pc.wQueen());
  EXPECT_EQ(2, pc.wRook());
  EXPECT_EQ(2, pc.wBishop());
  EXPECT_EQ(2, pc.wKnight());
  EXPECT_EQ(6, pc.wPawn());

  EXPECT_EQ(1, pc.bKing());
  EXPECT_EQ(1, pc.bQueen());
  EXPECT_EQ(2, pc.bRook());
  EXPECT_EQ(2, pc.bBishop());
  EXPECT_EQ(2, pc.bKnight());
  EXPECT_EQ(6, pc.bPawn());

  EXPECT_TRUE(pc.good());
}

//
// Test the ctor with a board
//
TEST(PieceCount3, BoardCtor)
{
  Board board;
  PieceCount pc(board);

  EXPECT_EQ(1, pc.wKing());
  EXPECT_EQ(1, pc.wQueen());
  EXPECT_EQ(2, pc.wRook());
  EXPECT_EQ(2, pc.wBishop());
  EXPECT_EQ(2, pc.wKnight());
  EXPECT_EQ(8, pc.wPawn());

  EXPECT_EQ(1, pc.bKing());
  EXPECT_EQ(1, pc.bQueen());
  EXPECT_EQ(2, pc.bRook());
  EXPECT_EQ(2, pc.bBishop());
  EXPECT_EQ(2, pc.bKnight());
  EXPECT_EQ(8, pc.bPawn());

  EXPECT_TRUE(pc.good());
}

//
// Test count
//
TEST(PieceCount4, Count)
{
  Board board;
  PieceCount pc(board);

  vector<Square> sqList;

  // add white queen
  auto wqueen = PieceColor::WHITE | PieceCode::QUEEN;
  sqList.emplace_back(0, 3, wqueen);

  // add white king
  auto wking = PieceColor::WHITE | PieceCode::KING;
  sqList.emplace_back(0, 4, wking);

  // add black queen
  auto bqueen = PieceColor::BLACK | PieceCode::QUEEN;
  sqList.emplace_back(7, 3, bqueen);

  // add black king
  auto bking = PieceColor::BLACK | PieceCode::KING;
  sqList.emplace_back(7, 4, bking);

  pc.count(sqList);

  EXPECT_EQ(1, pc.wKing());
  EXPECT_EQ(1, pc.wQueen());
  EXPECT_EQ(0, pc.wRook());
  EXPECT_EQ(0, pc.wBishop());
  EXPECT_EQ(0, pc.wKnight());
  EXPECT_EQ(0, pc.wPawn());

  EXPECT_EQ(1, pc.bKing());
  EXPECT_EQ(1, pc.bQueen());
  EXPECT_EQ(0, pc.bRook());
  EXPECT_EQ(0, pc.bBishop());
  EXPECT_EQ(0, pc.bKnight());
  EXPECT_EQ(0, pc.bPawn());

  EXPECT_TRUE(pc.good());

  pc.count(board);

  EXPECT_EQ(1, pc.wKing());
  EXPECT_EQ(1, pc.wQueen());
  EXPECT_EQ(2, pc.wRook());
  EXPECT_EQ(2, pc.wBishop());
  EXPECT_EQ(2, pc.wKnight());
  EXPECT_EQ(8, pc.wPawn());

  EXPECT_EQ(1, pc.bKing());
  EXPECT_EQ(1, pc.bQueen());
  EXPECT_EQ(2, pc.bRook());
  EXPECT_EQ(2, pc.bBishop());
  EXPECT_EQ(2, pc.bKnight());
  EXPECT_EQ(8, pc.bPawn());

  EXPECT_TRUE(pc.good());
}

//
// Test clear
//
TEST(PieceCount5, Clear)
{
  Board board;
  PieceCount pc(board);
  pc.clear();

  EXPECT_EQ(0, pc.white());
  EXPECT_EQ(0, pc.black());
}

//
// Test PieceCount::good()
//
TEST(PieceCount6, Good)
{
  PieceCount pc;
  vector<Square> sqList;

  // add two kings
  auto code = PieceColor::WHITE | PieceCode::KING;
  sqList.emplace_back(0, 0, code);
  sqList.emplace_back(0, 1, code);

  // not good
  pc.count(sqList);
  EXPECT_FALSE(pc.good());

  // clear squares and counts
  sqList.clear();
  pc.clear();

  // add 10 queens
  code = PieceColor::WHITE | PieceCode::QUEEN;
  sqList.emplace_back(0, 0, code);
  sqList.emplace_back(0, 1, code);
  sqList.emplace_back(0, 2, code);
  sqList.emplace_back(0, 3, code);
  sqList.emplace_back(0, 4, code);
  sqList.emplace_back(0, 5, code);
  sqList.emplace_back(0, 6, code);
  sqList.emplace_back(0, 7, code);
  sqList.emplace_back(1, 0, code);
  sqList.emplace_back(1, 1, code);

  // not good
  pc.count(sqList);
  EXPECT_FALSE(pc.good());

  // clear squares and counts
  sqList.clear();
  pc.clear();

  piececode_t pcArr[] = {
    PieceColor::WHITE | PieceCode::ROOK,
    PieceColor::WHITE | PieceCode::BISHOP,
    PieceColor::WHITE | PieceCode::KNIGHT
  };

  for (auto pcode : pcArr) {
    // add 11 pieces
    sqList.emplace_back(0, 0, pcode);
    sqList.emplace_back(0, 1, pcode);
    sqList.emplace_back(0, 2, pcode);
    sqList.emplace_back(0, 3, pcode);
    sqList.emplace_back(0, 4, pcode);
    sqList.emplace_back(0, 5, pcode);
    sqList.emplace_back(0, 6, pcode);
    sqList.emplace_back(0, 7, pcode);
    sqList.emplace_back(1, 0, pcode);
    sqList.emplace_back(1, 1, pcode);
    sqList.emplace_back(1, 2, pcode);

    // not good
    pc.count(sqList);
    EXPECT_FALSE(pc.good());

    // clear squares and counts
    sqList.clear();
    pc.clear();
  }

  // add 9 pawns
  code = PieceColor::WHITE | PieceCode::PAWN;
  sqList.emplace_back(0, 0, code);
  sqList.emplace_back(0, 1, code);
  sqList.emplace_back(0, 2, code);
  sqList.emplace_back(0, 3, code);
  sqList.emplace_back(0, 4, code);
  sqList.emplace_back(0, 5, code);
  sqList.emplace_back(0, 6, code);
  sqList.emplace_back(0, 7, code);
  sqList.emplace_back(1, 0, code);

  // not good
  pc.count(sqList);
  EXPECT_FALSE(pc.good());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
