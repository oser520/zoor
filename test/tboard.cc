/////////////////////////////////////////////////////////////////////////////////////
/// @file tboard.cc
/// @author Omar A Serrano
/// @date 2016-03-19
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "fenrecord.hh"
#include "iofen.hh"
#include "piecemove.hh"
#include "square.hh"

//
// gtest
//
#include "gtest/gtest.h"

namespace {

//
// from STL
//
using std::ostringstream;
using std::pair;
using std::vector;

//
// from zoor
//
using namespace zoor;

//
// test Board default ctor
//
TEST(Board, DefaultCtor)
{
  Board board;
  EXPECT_FALSE(board.canCastle());
  EXPECT_FALSE(board.canCastleLong());
  EXPECT_EQ(Color::W, board.nextTurn());

  auto pm = board.lastMove();
  EXPECT_EQ(0, pm.sRow());
  EXPECT_EQ(0, pm.sColumn());
  EXPECT_EQ(0, pm.sCode());
  EXPECT_EQ(0, pm.dRow());
  EXPECT_EQ(0, pm.dColumn());
  EXPECT_EQ(0, pm.dCode());
  EXPECT_EQ(0, pm.xRow());
  EXPECT_EQ(0, pm.xColumn());
  EXPECT_EQ(0, pm.xCode());

  auto sq = board(0, 0);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
  EXPECT_EQ(Piece::R, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(6, 2);
  EXPECT_EQ(6, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::P, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(7, 2);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::B, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 3);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(3, sq.column());
  EXPECT_EQ(Piece::Q, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(7, 4);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(4, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 5);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(Piece::B, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(7, 6);
  EXPECT_EQ(7, sq.row());
  EXPECT_EQ(6, sq.column());
  EXPECT_EQ(Piece::N, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  sq = board(0, 7);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(7, sq.column());
  EXPECT_EQ(Piece::R, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(4, 5);
  EXPECT_EQ(4, sq.row());
  EXPECT_EQ(5, sq.column());
  EXPECT_EQ(Piece::NONE, sq.piece());
  EXPECT_EQ(Color::NONE, sq.color());
}

//
// test ctor with 4 param
//
TEST(Board, CtorWithVectorColorInfoMoveParam)
{
  vector<Square> sqList;
  sqList.emplace_back(0, 0, Piece::K, Color::W);
  sqList.emplace_back(0, 2, Piece::K, Color::B);

  BoardInfo info;
  info.rookA1On().rookA8On().rookH1On().rookH8On();

  PieceMove pm(0, 3, Color::B|Piece::K, 0, 2);

  Board board(sqList, Color::W, info, pm);

  EXPECT_EQ(Color::W, board.nextTurn());
  EXPECT_EQ(pm, board.lastMove());
  EXPECT_FALSE(board.canCastle());
  EXPECT_FALSE(board.canCastleLong());

  auto sq = board(0, 0);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(0, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::W, sq.color());

  sq = board(0, 1);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(1, sq.column());
  EXPECT_EQ(0, sq.code());

  sq = board(0, 2);
  EXPECT_EQ(0, sq.row());
  EXPECT_EQ(2, sq.column());
  EXPECT_EQ(Piece::K, sq.piece());
  EXPECT_EQ(Color::B, sq.color());

  // check other squares in first row are empty
  for (int i = 3; i < BasicBoard::DIM; ++i)
    EXPECT_EQ(0, board(0, i).code());

  // check other squares in board are empty
  for (int i = 1; i < BasicBoard::DIM; ++i) {
    for (int j = 1; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(0, board(i, j).code());
  }
}

//
// test canCastle and canCastleLong for white
//
TEST(Board, CanWhiteCastle)
{
  vector<FenRecord> fenList = readFen("fen/canWhiteCastle.fen");

  // first bool is expected for canCastle()
  // second bool is expected for canCastleLong()
  vector<pair<bool, bool>> boolList = {
    {true, true},   // k7/8/8/8/4n3/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/4n3/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/4n3/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/8/7n/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/6n1/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/8/8/8/n7/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/8/8/b7/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/4b3/8/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/4b3/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/7b/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/b7/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/4r3/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/5r2/8/8/8/8/8/R3K2R w KQ - 0 40
    {true, true},   // k7/7r/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/2r3r1/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/7q/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/7q/8/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/7q/8/8/8/R3K2R w KQ - 0 40
    {true, false},  // k7/8/7q/8/8/8/8/R3K2R w KQ - 0 40
    {true, true},   // k7/7q/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/4q3/8/8/8/8/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/8/Rq2K2R w KQ - 0 40
    {false, true},  // k7/8/8/8/8/8/7p/R3K2R w KQ - 0 40
    {true, true},   // k7/8/8/8/8/7p/8/R3K2R w KQ - 0 40
    {false, false}, // k7/8/8/8/8/8/4p3/R3K2R w KQ - 0 40
    {true, false},  // k7/8/8/8/8/8/2p5/R3K2R w KQ - 0 40
    {true, false},  // 8/8/8/8/8/8/1k6/R3K2R w KQ - 0 40
    {false, true},  // 8/8/8/8/8/8/6k1/R3K2R w KQ - 0 40
    {true, true}    // 8/8/8/8/8/6k1/8/R3K2R w KQ - 0 40
  };

  // make sure we don't omit any tests
  EXPECT_EQ(fenList.size(), boolList.size());

  auto fenIt = fenList.cbegin();
  for (const auto &bools : boolList) {
    auto pb = fenIt->boardPtr();
    EXPECT_EQ(bools.first, pb->canCastle());
    EXPECT_EQ(bools.second, pb->canCastleLong());
    ++fenIt;
  }
}

//
// test canCaslte and canCastleLong for black
//
TEST(Board, CanBlackCastle)
{
  vector<FenRecord> fenList = readFen("fen/canBlackCastle.fen");

  // first bool is expected for canCastle()
  // second bool is expected for canCastleLong()
  vector<pair<bool, bool>> boolList = {
    {true, true},   // r3k2r/8/8/4N3/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/4N3/8/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/4N3/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/7N/8/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/8/6N1/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/N7/8/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/B7/8/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/4B3/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/4B3/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/8/7B/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/B7/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/4R3/7K b kq - 0 40
    {false, true},  // r3k2r/8/8/8/8/8/5R2/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/8/8/8/7R/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/2R3R1/7K b kq - 0 40
    {false, true},  // r3k2r/8/7Q/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/7Q/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/8/8/8/7Q/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/8/8/8/8/7Q/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/8/8/8/8/7Q/7K b kq - 0 40
    {false, false}, // r3k2r/8/8/8/8/8/4Q3/7K b kq - 0 40
    {false, false}, // rQ2k2r/8/8/8/8/8/8/7K b kq - 0 40
    {false, true},  // r3k2r/7P/8/8/8/8/8/7K b kq - 0 40
    {true, true},   // r3k2r/8/7P/8/8/8/8/7K b kq - 0 40
    {false, false}, // r3k2r/4P3/8/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/2P5/8/8/8/8/8/7K b kq - 0 40
    {true, false},  // r3k2r/1K6/8/8/8/8/8/8 b kq - 0 40
    {false, true},  // r3k2r/6K1/8/8/8/8/8/8 b kq - 0 40
    {true, true}    // r3k2r/8/6K1/8/8/8/8/8 b kq - 0 40
  };

  // make sure we don't omit any tests
  EXPECT_EQ(fenList.size(), boolList.size());

  auto fenIt = fenList.cbegin();
  for (const auto &bools : boolList) {
    auto pb = fenIt->boardPtr();
    EXPECT_EQ(bools.first, pb->canCastle());
    EXPECT_EQ(bools.second, pb->canCastleLong());
    ++fenIt;
  }
}

//
// test getMoves with row and column specified
//
TEST(Board, DISABLED_GetMovesRowCol)
{
  // TODO
}

//
// test getMoves for all moves on the board
//
TEST(Board, DISABLED_GetMoves)
{
  // TODO
}

//
// test getBoards
//
TEST(Board, DISABLED_GetBoards)
{
  // TODO
}

//
// test makeMoveCopy
//
TEST(Board, DISABLED_MakeMoveCopy)
{
  // TODO
}

//
// test makeMove
//
TEST(Board, DISABLED_MakeMove)
{
  // TODO
}

//
// test lastMove
//
TEST(Board, DISABLED_LastMove)
{
  // TODO
}

//
// test operator()
//
TEST(Board, DISABLED_CallOp)
{
  // TODO
}

//
// test iterators
//
TEST(Board, Iterators)
{
  Board board;
  auto it = board.begin();

  EXPECT_EQ(Color::W|Piece::R, *it);
  EXPECT_EQ(Color::W|Piece::N, *(it+6));
  EXPECT_EQ(Color::W|Piece::R, *(it+7));

  for (int i = 0; i < BasicBoard::DIM; ++i) {
    for (int j = 0; j < BasicBoard::DIM; ++j)
      EXPECT_EQ(board(i, j).code(), *it++);
  }

  EXPECT_EQ(board.end(), it);
}

//
// test jump
//
TEST(Board, DISABLED_Jump)
{
  // TODO
}

//
// test isCheckPawn
//
TEST(Board, DISABLED_IsCheckPawn)
{
  // TODO
}

//
// test isCheckKnight
//
TEST(Board, DISABLED_IsCheckKnight)
{
  // TODO
}

//
// test isCheckBishop
//
TEST(Board, DISABLED_IsCheckBishop)
{
  // TODO
}

//
// test isCheckRook
//
TEST(Board, DISABLED_IsCheckRook)
{
  // TODO
}

//
// test isCheckQueen
//
TEST(Board, DISABLED_IsCheckQueen)
{
  // TODO
}

//
// test isCheckKing
//
TEST(Board, DISABLED_IsCheckKing)
{
  // TODO
}

//
// test isCheck
//
TEST(Board, DISABLED_IsCheck)
{
  // TODO
}

//
// test isEnPassant on white's turn
//
TEST(Board, IsEnPassantForWhite)
{
  auto fenList = readFen("fen/enPassantForWhite.fen");

  EXPECT_EQ(16, fenList.size());

  for (int col = 0, i = 0; col < 8; ++col, i += 2) {
    auto pb = fenList[i].boardPtr();
    EXPECT_TRUE(pb->isEnPassant(Color::W, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
    pb = fenList[i+1].boardPtr();
    EXPECT_FALSE(pb->isEnPassant(Color::W, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
  }
}

//
// test isEnPassant on black's turn
//
TEST(Board, IsEnPassantForBlack)
{
  auto fenList = readFen("fen/enPassantForBlack.fen");

  EXPECT_EQ(16, fenList.size());

  for (int col = 0, i = 0; col < 8; ++col, i += 2) {
    auto pb = fenList[i].boardPtr();
    EXPECT_TRUE(pb->isEnPassant(Color::B, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
    pb = fenList[i+1].boardPtr();
    EXPECT_FALSE(pb->isEnPassant(Color::B, col))
      << "\tchecking on column " << col
      << " the last move is " << pb->lastMove();
  }
}

//
// test movePawn on white's turn
//
TEST(Board, MoveWhitePawn)
{
  auto fenList = readFen("fen/moveWhitePawn.fen");

  vector<PieceMove> moveList;
  auto wpawn = Color::W | Piece::P;

  // FEN 1: k7/p7/8/8/8/2p5/1P6/4K3 w - - 0 40
  moveList.emplace_back(1, 1, wpawn, 2, 1);
  moveList.emplace_back(1, 1, wpawn, 3, 1);
  moveList.emplace_back(1, 1, wpawn, 2, 2);
  moveList.back().xPiece(2, 2, Piece::P, Color::B);
  auto pb = fenList[0].boardPtr();
  auto pawnMoveList = pb->movePawn(1, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  auto ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 2: k7/p7/8/8/8/r1p5/1P6/4K3 w - - 0 40
  moveList.emplace_back(1, 1, wpawn, 2, 0);
  moveList.back().xPiece(2, 0, Piece::R, Color::B);
  pb = fenList[1].boardPtr();
  pawnMoveList = pb->movePawn(1, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList)
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it));

  // FEN 3: k7/p7/8/8/8/1p6/1P6/4K3 w - - 0 40
  pb = fenList[2].boardPtr();
  EXPECT_EQ(0, pb->movePawn(1, 1).size());

  // FEN 4: k7/p7/8/8/8/1P6/8/4K3 w - - 0 40
  pb = fenList[3].boardPtr();
  pawnMoveList = pb->movePawn(2, 1);
  EXPECT_EQ(1, pawnMoveList.size());
  EXPECT_EQ(PieceMove(2, 1, wpawn, 3, 1), pawnMoveList.front());

  // FEN 5: k7/8/p7/1Pp5/8/8/8/4K3 w - c6 0 40
  moveList.clear();
  moveList.emplace_back(4, 1, wpawn, 5, 0);
  moveList.back().xPiece(5, 0, Piece::P, Color::B);
  moveList.emplace_back(4, 1, wpawn, 5, 1);
  moveList.emplace_back(4, 1, wpawn, 5, 2);
  moveList.back().xPiece(4, 2, Piece::P, Color::B);
  pb = fenList[4].boardPtr();
  pawnMoveList = pb->movePawn(4, 1);
  EXPECT_EQ(moveList.size(), pawnMoveList.size());
  ite = pawnMoveList.cend();
  for (const auto it : moveList) {
    EXPECT_NE(ite, std::find(pawnMoveList.cbegin(), ite, it))
      << "\tPieceMove not found: " << it
      << "\n\tisEnPassant(white, 2): "
      << pb->isEnPassant(Color::W, 2);
  }
}

//
// test moveKnight
//
TEST(Board, DISABLED_MoveKnight)
{
  // TODO
}

//
// test moveBishop
//
TEST(Board, DISABLED_MoveBishop)
{
  // TODO
}

//
// test moveRook
//
TEST(Board, DISABLED_MoveRook)
{
  // TODO
}

//
// test moveQueen
//
TEST(Board, DISABLED_MoveQueen)
{
  // TODO
}

//
// test moveKing
//
TEST(Board, DISABLED_MoveKing)
{
  // TODO
}

//
// test toString
//
TEST(Board, DISABLED_ToString)
{
  // TODO
}

//
// test hashCode
//
TEST(Board, DISABLED_HashCode)
{
  // TODO
}

//
// test colorToMove
//
TEST(Board, DISABLED_NextTurn)
{
  // TODO
}

//
// test equality operator
//
TEST(Board, DISABLED_EqualOp)
{
  // TODO
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
