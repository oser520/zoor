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
#include "basictypes.hh"
#include "board.hh"
#include "piececount.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace zoor {

//
// using from STL
//
using std::ostringstream;
using std::string;
using std::vector;

//
// Test the default ctor
//
TEST(PieceCount, DefaultCtor)
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
TEST(PieceCount, SquareListCtor)
{
  vector<Square> sqList;

  // add white pawns
  auto piece = Color::W | Piece::P;
  sqList.emplace_back(1, 0, piece);
  sqList.emplace_back(1, 1, piece);
  sqList.emplace_back(1, 2, piece);
  sqList.emplace_back(1, 3, piece);
  sqList.emplace_back(1, 4, piece);
  sqList.emplace_back(1, 5, piece);

  // add white knights
  piece = Color::W | Piece::N;
  sqList.emplace_back(0, 1, piece);
  sqList.emplace_back(0, 6, piece);

  // add white bishops
  piece = Color::W | Piece::B;
  sqList.emplace_back(0, 2, piece);
  sqList.emplace_back(0, 5, piece);

  // add white rook
  piece = Color::W | Piece::R;
  sqList.emplace_back(0, 0, piece);
  sqList.emplace_back(0, 7, piece);

  // add white queen
  piece = Color::W | Piece::Q;
  sqList.emplace_back(0, 3, piece);

  // add white king
  piece = Color::W | Piece::K;
  sqList.emplace_back(0, 4, piece);

  // add black pawns
  piece = Color::B | Piece::P;
  sqList.emplace_back(6, 0, piece);
  sqList.emplace_back(6, 1, piece);
  sqList.emplace_back(6, 2, piece);
  sqList.emplace_back(6, 3, piece);
  sqList.emplace_back(6, 4, piece);
  sqList.emplace_back(6, 5, piece);

  // add black knights
  piece = Color::B | Piece::N;
  sqList.emplace_back(7, 1, piece);
  sqList.emplace_back(7, 6, piece);

  // add black bishops
  piece = Color::B | Piece::B;
  sqList.emplace_back(7, 2, piece);
  sqList.emplace_back(7, 5, piece);

  // add black rook
  piece = Color::B | Piece::R;
  sqList.emplace_back(7, 0, piece);
  sqList.emplace_back(7, 7, piece);

  // add black queen
  piece = Color::B | Piece::Q;
  sqList.emplace_back(7, 3, piece);

  // add black king
  piece = Color::B | Piece::K;
  sqList.emplace_back(7, 4, piece);

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
TEST(PieceCount, BoardCtor)
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
TEST(PieceCount, Count)
{
  Board board;
  PieceCount pc(board);

  vector<Square> sqList;

  sqList.emplace_back(0, 3, Piece::Q, Color::W);
  sqList.emplace_back(0, 4, Piece::K, Color::W);
  sqList.emplace_back(7, 3, Piece::Q, Color::B);
  sqList.emplace_back(7, 4, Piece::K, Color::B);

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
TEST(PieceCount, Clear)
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
TEST(PieceCount, Good)
{
  PieceCount pc;
  vector<Square> sqList;

  // add two kings
  auto code = Color::W | Piece::K;
  sqList.emplace_back(0, 0, code);
  sqList.emplace_back(0, 1, code);

  // not good
  pc.count(sqList);
  EXPECT_FALSE(pc.good());

  // clear squares and counts
  sqList.clear();
  pc.clear();

  // add 10 queens
  code = Color::W | Piece::Q;
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

  piece_t pcArr[] = {
    Color::W | Piece::R,
    Color::W | Piece::B,
    Color::W | Piece::N
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
  code = Color::W | Piece::P;
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

} // namespace zoor
