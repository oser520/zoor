/////////////////////////////////////////////////////////////////////////////////////
//! @file tiofen.cc
//! @author Omar A Serrano
//! @date 2016-04-21
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "boardinfo.hh"
#include "iofen.hh"
#include "piecemove.hh"
#include "square.hh"

//
// gtest header
//
#include "gtest/gtest.h"

namespace zoor {

//
// using from STL
//
using std::vector;

//
// Test readFen with a record that represents the initial position
//
TEST(IOFen, DefaultBoard)
{
  Board board;
  auto fenList = readFen("fen/init.fen");

  EXPECT_EQ(1, fenList.size());

  auto fenrec = fenList.front();
  EXPECT_EQ(0, fenrec.halfMove());
  EXPECT_EQ(1, fenrec.fullMove());
  EXPECT_EQ(board, *fenrec.boardPtr());
  EXPECT_EQ(Color::W, fenrec.boardPtr()->nextTurn());
}

//
// Test reading a fen file that only contains one line
//
TEST(IOFen, Test1)
{
  vector<Square> sqList;

  // add the black pieces
  sqList.emplace_back(7, 4, Piece::K, Color::B);
  sqList.emplace_back(7, 7, Piece::R, Color::B);
  sqList.emplace_back(6, 4, Piece::P, Color::B);
  sqList.emplace_back(6, 6, Piece::P, Color::B);

  // add the white pieces
  sqList.emplace_back(3, 2, Piece::N, Color::W);
  sqList.emplace_back(0, 3, Piece::Q, Color::W);
  sqList.emplace_back(0, 4, Piece::K, Color::W);

  // only black king can do short castling
  BoardInfo info;
  info.rookA1On().rookH1On().rookA8On();

  Board board(sqList, Color::W, info);

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
TEST(IOFen, Test2)
{
  // read the FEN records
  auto fenList = readFen("fen/test2.fen");
  EXPECT_EQ(19, fenList.size());

  for (auto& fenrec : fenList) {
    EXPECT_EQ(0, fenrec.halfMove());
    EXPECT_EQ(40, fenrec.fullMove());
  }

  // check next color to move
  EXPECT_EQ(Color::B, fenList[0].boardPtr()->nextTurn());

  for (int i = 1; i < 10; ++i)
    EXPECT_EQ(Color::W, fenList[i].boardPtr()->nextTurn());

  for (int i = 10; i < 19; ++i)
    EXPECT_EQ(Color::B, fenList[i].boardPtr()->nextTurn());

  // no castling rights on all tests
  BoardInfo info;
  info.rookA1On().rookA8On().rookH1On().rookH8On();

  vector<Square> sqList;
  // position in 1st fen line
  // add the black pieces
  sqList.emplace_back(6, 2, Piece::K, Color::B);
  sqList.emplace_back(4, 1, Piece::P, Color::B);
  // add the white pieces
  sqList.emplace_back(2, 4, Piece::K, Color::W);
  sqList.emplace_back(4, 5, Piece::P, Color::W);

  // compare againts 1st fen line
  Board board1(sqList, Color::B, info);
  EXPECT_EQ(board1, *fenList[0].boardPtr());

  // compare against 2nd fen line
  sqList[0].location(7, 1);
  Board board2(sqList, Color::W, info);
  EXPECT_EQ(board2, *fenList[1].boardPtr());

  // compare against 3rd fen line
  sqList[0].column(2);
  Board board3(sqList, Color::W, info);
  EXPECT_EQ(board3, *fenList[2].boardPtr());

  // compare against 4th fen line
  sqList[0].column(3);
  Board board4(sqList, Color::W, info);
  EXPECT_EQ(board4, *fenList[3].boardPtr());

  // compare against 5th fen line
  sqList[0].location(6, 1);
  Board board5(sqList, Color::W, info);
  EXPECT_EQ(board5, *fenList[4].boardPtr());

  // compare against 6th fen line
  sqList[0].column(3);
  Board board6(sqList, Color::W, info);
  EXPECT_EQ(board6, *fenList[5].boardPtr());

  // compare against 7th fen line
  sqList[0].location(5, 1);
  Board board7(sqList, Color::W, info);
  EXPECT_EQ(board7, *fenList[6].boardPtr());

  // compare against 8th fen line
  sqList[0].column(2);
  Board board8(sqList, Color::W, info);
  EXPECT_EQ(board8, *fenList[7].boardPtr());

  // compare against 9th fen line
  sqList[0].column(3);
  Board board9(sqList, Color::W, info);
  EXPECT_EQ(board9, *fenList[8].boardPtr());

  // compare against 10th fen line
  sqList[0].location(6, 2);
  sqList[1].location(3, 1);
  Board board10(sqList, Color::W, info);
  EXPECT_EQ(board10, *fenList[9].boardPtr());

  // compare against 11th fen line
  sqList[1].row(4);
  sqList[2].location(3, 3);
  Board board11(sqList, Color::B, info);
  EXPECT_EQ(board11, *fenList[10].boardPtr());

  // compare against 12th fen line
  sqList[2].column(4);
  Board board12(sqList, Color::B, info);
  EXPECT_EQ(board12, *fenList[11].boardPtr());

  // compare against 13th fen line
  sqList[2].column(5);
  Board board13(sqList, Color::B, info);
  EXPECT_EQ(board13, *fenList[12].boardPtr());

  // compare against 14th fen line
  sqList[2].location(2, 3);
  Board board14(sqList, Color::B, info);
  EXPECT_EQ(board14, *fenList[13].boardPtr());

  // compare against 15th fen line
  sqList[2].column(5);
  Board board15(sqList, Color::B, info);
  EXPECT_EQ(board15, *fenList[14].boardPtr());

  // compare against 16th fen line
  sqList[2].location(1, 3);
  Board board16(sqList, Color::B, info);
  EXPECT_EQ(board16, *fenList[15].boardPtr());

  // compare against 17th fen line
  sqList[2].column(4);
  Board board17(sqList, Color::B, info);
  EXPECT_EQ(board17, *fenList[16].boardPtr());

  // compare against 18th fen line
  sqList[2].column(5);
  Board board18(sqList, Color::B, info);
  EXPECT_EQ(board18, *fenList[17].boardPtr());

  // compare against 19th fen line
  sqList[2].location(2, 4);
  sqList[3].location(5, 5);
  Board board19(sqList, Color::B, info);
  EXPECT_EQ(board19, *fenList[18].boardPtr());
}

//
// Verify readFen can parse en passant information
//
TEST(IOFen, Test3)
{
  vector<Square> sqList;

  // create the pieces for the board
  sqList.emplace_back(7, 4, Piece::K, Color::B);
  sqList.emplace_back(0, 4, Piece::K, Color::W);
  sqList.emplace_back(3, 4, Piece::P, Color::W);

  // only black king can do short castling
  BoardInfo info;
  info.rookA1On().rookH1On().rookA8On().rookH8On();

  // last move
  PieceMove pm(1, 4, Color::W|Piece::P, 3, 4);

  Board board(sqList, Color::B, info, pm);

  auto fenList = readFen("fen/test3.fen");

  EXPECT_EQ(1, fenList.size());
  EXPECT_EQ(0, fenList[0].halfMove());
  EXPECT_EQ(39, fenList[0].fullMove());
  EXPECT_EQ(board, *fenList[0].boardPtr());
}

} // namespace zoor
