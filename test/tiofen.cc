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
#include "piecemove.hh"
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
using zoor::PieceMove;
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
  EXPECT_EQ(PieceColor::WHITE, fenrec.boardPtr()->colorToMove());
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

//
// Test reading a fen file with 18 records
//
TEST(IOFen3, test2)
{
  // read the FEN records
  auto fenList = readFen("fen/test2.fen");
  EXPECT_EQ(19, fenList.size());

  for (auto& fenrec : fenList) {
    EXPECT_EQ(0, fenrec.halfMove());
    EXPECT_EQ(40, fenrec.fullMove());
  }

  // check next color to move
  EXPECT_EQ(PieceColor::BLACK, fenList[0].boardPtr()->colorToMove());

  for (int i = 1; i < 10; ++i)
    EXPECT_EQ(PieceColor::WHITE, fenList[i].boardPtr()->colorToMove());

  for (int i = 10; i < 20; ++i)
    EXPECT_EQ(PieceColor::BLACK, fenList[i].boardPtr()->colorToMove());

  // default BoardInfo on all tests
  BoardInfo info;

  vector<Square> sqList;
  // position in 1st fen line
  // add the black pieces
  sqList.emplace_back(6, 2,  PieceCode::KING, PieceColor::BLACK);
  sqList.emplace_back(4, 1, PieceCode::PAWN, PieceColor::BLACK);
  // add the white pieces
  sqList.emplace_back(2, 4, PieceCode::KING, PieceColor::WHITE);
  sqList.emplace_back(4, 5, PieceCode::PAWN, PieceColor::WHITE);

  // compare againts 1st fen line
  Board board1(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board1, *fenList[0].boardPtr());

  // compare against 2nd fen line
  sqList[0].setLocation(7, 1);
  Board board2(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board2, *fenList[1].boardPtr());

  // compare against 3rd fen line
  sqList[0].setColumn(2);
  Board board3(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board3, *fenList[2].boardPtr());

  // compare against 4th fen line
  sqList[0].setColumn(3);
  Board board4(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board4, *fenList[3].boardPtr());

  // compare against 5th fen line
  sqList[0].setLocation(6, 1);
  Board board5(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board5, *fenList[4].boardPtr());

  // compare against 6th fen line
  sqList[0].setColumn(3);
  Board board6(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board6, *fenList[5].boardPtr());

  // compare against 7th fen line
  sqList[0].setLocation(5, 1);
  Board board7(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board7, *fenList[6].boardPtr());

  // compare against 8th fen line
  sqList[0].setColumn(2);
  Board board8(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board8, *fenList[7].boardPtr());

  // compare against 9th fen line
  sqList[0].setColumn(3);
  Board board9(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board9, *fenList[8].boardPtr());

  // compare against 10th fen line
  sqList[0].setLocation(6, 2);
  sqList[1].setLocation(3, 1);
  Board board10(sqList, PieceColor::WHITE, info);
  EXPECT_EQ(board10, *fenList[9].boardPtr());

  // compare against 11th fen line
  sqList[1].setRow(4);
  sqList[2].setLocation(3, 3);
  Board board11(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board11, *fenList[10].boardPtr());

  // compare against 12th fen line
  sqList[2].setColumn(4);
  Board board12(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board12, *fenList[11].boardPtr());

  // compare against 13th fen line
  sqList[2].setColumn(5);
  Board board13(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board13, *fenList[12].boardPtr());

  // compare against 14th fen line
  sqList[2].setLocation(2, 3);
  Board board14(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board14, *fenList[13].boardPtr());

  // compare against 15th fen line
  sqList[2].setColumn(5);
  Board board15(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board15, *fenList[14].boardPtr());

  // compare against 16th fen line
  sqList[2].setLocation(1, 3);
  Board board16(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board16, *fenList[15].boardPtr());

  // compare against 17th fen line
  sqList[2].setColumn(4);
  Board board17(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board17, *fenList[16].boardPtr());

  // compare against 18th fen line
  sqList[2].setColumn(5);
  Board board18(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board18, *fenList[17].boardPtr());

  // compare against 19th fen line
  sqList[2].setLocation(2, 4);
  sqList[3].setLocation(5, 5);
  Board board19(sqList, PieceColor::BLACK, info);
  EXPECT_EQ(board19, *fenList[18].boardPtr());
}

//
// Verify readFen can parse en passant information
//
TEST(IOFen4, test3)
{
  vector<Square> sqList;

  // create the pieces for the board
  sqList.emplace_back(7, 4, PieceCode::KING, PieceColor::BLACK);

  sqList.emplace_back(0, 4, PieceCode::KING, PieceColor::WHITE);
  sqList.emplace_back(3, 4, PieceCode::PAWN, PieceColor::WHITE);

  // only black king can do short castling
  BoardInfo info;
  info.rookA1On().rookH1On().rookA8On().rookH8On();

  // last move
  PieceMove pm(1, 4, PieceColor::WHITE|PieceCode::PAWN, 3, 4);

  Board board(sqList, PieceColor::BLACK, info, pm);

  auto fenList = readFen("fen/test3.fen");

  EXPECT_EQ(1, fenList.size());
  EXPECT_EQ(0, fenList[0].halfMove());
  EXPECT_EQ(39, fenList[0].fullMove());
  EXPECT_EQ(board, *fenList[0].boardPtr());
}

} // namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
