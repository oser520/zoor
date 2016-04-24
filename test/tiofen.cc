/////////////////////////////////////////////////////////////////////////////////////
/// @file tiofen.cc
/// @author Omar A Serrano
/// @date 2016-04-21
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <vector>

//
// zoor headers
//
#include "board.hh"
#include "boardinfo.hh"
#include "fennotation.hh"
#include "piececode.hh"
#include "square.hh"

//
// gtest header
//
#include "gtest/gtest.h"

namespace {

//
// using from STL
//
using std::vector;

//
// using from zoor
//
using zoor::Board;
using zoor::BoardInfo;
using zoor::PieceCode;
using zoor::PieceColor;
using zoor::Square;
using zoor::readFen;

//
// Test readFen with a record that represents the initial position
//
TEST(IOFen1, defaultBoard)
{
  Board board;
  auto fenList = readFen("fen/init.fen");

  EXPECT_EQ(1, fenList.size());

  auto fenrec = fenList.front();
  EXPECT_EQ(0, fenrec.halfMove());
  EXPECT_EQ(1, fenrec.fullMove());
  EXPECT_EQ(board, *fenrec.boardPtr());
}

//
// Test reading a fen file that only contains one line
//
TEST(IOFen2, test1)
{
  vector<Square> sqList;

  // add the black pieces
  sqList.emplace_back(7, 4, PieceCode::KING, PieceColor::BLACK);
  sqList.emplace_back(7, 7, PieceCode::ROOK, PieceColor::BLACK);
  sqList.emplace_back(6, 4, PieceCode::PAWN, PieceColor::BLACK);
  sqList.emplace_back(6, 6, PieceCode::PAWN, PieceColor::BLACK);

  // add the white pieces
  sqList.emplace_back(3, 2, PieceCode::KNIGHT, PieceColor::WHITE);
  sqList.emplace_back(0, 3, PieceCode::QUEEN, PieceColor::WHITE);
  sqList.emplace_back(0, 4, PieceCode::KING, PieceColor::WHITE);

  // only black king can do short castling
  BoardInfo info;
  info.rookA1On().rookH1On().rookA8On();

  Board board(sqList, PieceColor::WHITE, info);

  auto fenList = readFen("fen/test1.fen");

  EXPECT_EQ(1, fenList.size());

  auto fenrec = fenList.front();
  EXPECT_EQ(0, fenrec.halfMove());
  EXPECT_EQ(33, fenrec.fullMove());
  EXPECT_EQ(board, *fenrec.boardPtr());
}

} // namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
