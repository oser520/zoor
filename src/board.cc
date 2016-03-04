/**
 * @file board.cc
 * @author Omar A Serrano
 * @date 2015-12-26
 */

// STL headers
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <bitset>

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemove.hh"
#include "board.hh"

namespace zoor {

////////////////////////////////////////////////////////////////////////////////
// aliases
////////////////////////////////////////////////////////////////////////////////
using dim_type = Board::dim_type;
using jump_list = Board::jump_list;

////////////////////////////////////////////////////////////////////////////////
// initialize static vars
////////////////////////////////////////////////////////////////////////////////
const jump_list Board::JUMP_KNIGHT = {
  {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
  {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

const jump_list Board::JUMP_KING = {
  {1, 0}, {1, 1}, {0, 1}, {-1, 1},
  {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};

const std::array<Board::row_type, Board::BOARD_DIM>
Board::INIT_BOARD = {
//    a     b     c     d     e     f     g     h
    {0x0c, 0x0a, 0x0b, 0x0d, 0x0e, 0x0b, 0x0a, 0x0c}, // 1
    {0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09}, // 2
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 3
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 4
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 5
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 6
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}, // 7
    {0x14, 0x12, 0x13, 0x15, 0x16, 0x13, 0x12, 0x14}, // 8
};

////////////////////////////////////////////////////////////////////////////////
// default ctor
////////////////////////////////////////////////////////////////////////////////
Board::Board()
  : mRows(INIT_BOARD),
    mColor(PieceColor::WHITE) {}

////////////////////////////////////////////////////////////////////////////////
// check if position is valid in board
////////////////////////////////////////////////////////////////////////////////
bool Board::isInBound(dim_type position) const noexcept
{
  return position >= 0 && position < BOARD_DIM;
}

////////////////////////////////////////////////////////////////////////////////
// check if row and column are within bounds of board
////////////////////////////////////////////////////////////////////////////////
bool Board::isInBound(dim_type row, dim_type column) const noexcept
{
  return row >= 0 && column < BOARD_DIM
      && column >= 0 && column < BOARD_DIM;
}

////////////////////////////////////////////////////////////////////////////////
// check if king can do short castling
////////////////////////////////////////////////////////////////////////////////
bool Board::canCastle() const noexcept
{
  dim_type row;
  size_t bit;

  // row and shift parameter for color
  if (isWhite(mColor)) {
    row = 0;
    bit = RK_H1_MOVED;
  } else {
    row = 7;
    bit = RK_H8_MOVED;
  }

  // check conditions
  // 1. rook a1 or a8 has not moved
  // 2. king has not moved
  // 3. king is not in check
  bool cond = mBoardInfo[bit++];
  cond |= mBoardInfo[++bit];
  cond |= mBoardInfo[++bit];

  // any of the 3 conditions are true
  if (cond)
    return false;

  // path for castling is clear
  if (!isPieceNone(get(row, 5)) || !isPieceNone(get(row, 6)))
    return false;

  // no checks on path to castle
  if (isCheck(row, 5) || isCheck(row, 6))
    return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// check if king can do long castling
////////////////////////////////////////////////////////////////////////////////
bool Board::canCastleLong() const noexcept
{
  dim_type row;
  size_t bit;

  // row and shift parameter for color
  if (isWhite(mColor)) {
    row = 1;
    bit = RK_A1_MOVED;
  } else {
    row = 7;
    bit = RK_A8_MOVED;
  }

  // check conditions
  // 1. rook h1 or h8 has not moved
  // 2. king has not moved
  // 3. king is not in check
  bool cond = mBoardInfo[bit];
  cond |= mBoardInfo[++bit];
  cond |= mBoardInfo[++bit];

  // any of the 3 conditions are true
  if (cond)
    return false;

  // path for castling is clear
  if (!isPieceNone(get(row, 3)) || !isPieceNone(get(row, 2)))
    return false;

  // no checks on path to castle
  if (isCheck(row, 3) || isCheck(row, 2))
    return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// return a reference to the rows
////////////////////////////////////////////////////////////////////////////////
const std:array<row_type, Board::BOARD_DIM>&
Board::rows() const noexcept
{
  return mRows;
}

////////////////////////////////////////////////////////////////////////////////
// return a copy of the rows
////////////////////////////////////////////////////////////////////////////////
std:array<row_type, Board::BOARD_DIM>
Board::rowsCopy() const
{
  auto rc(mRows);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
// get the moves that can be made from a given square
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove> getMoves(dim_type row, dim_type colum) const
{
  assert(!isColorNone(mColor));
  std::vector<PieceMove> moveList;

  auto code = get(row, column);

  if (isPieceNone(code) || !isSameColor(code, mColor))
    return moveList;

  switch (getPieceCode(code)) {
  case PieceCode::PAWN:
    moveList = movePawn(row, column);
    break;
  case PieceCode::KNIGHT:
    moveList = moveKnight(row, column);
    break;
  case PieceCode::BISHOP:
    moveList = moveBishop(row, column);
    break;
  case PieceCode::ROOK:
    moveList = moveRook(row, column);
    break;
  case PieceCode::QUEEN:
    moveList = moveQueen(row, column);
    break;
  case PieceCode::KING:
    moveList = moveKing(row, column);
    break;
  default:
    // should never get here
    assert(false);
    break;
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// get all the moves from all the pieces
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove> Board::getMoves() const
{
  assert(!isColorNone(mColor));

  std::vector<PieceMove> moveList;

  for (dim_type row = 0; row < BOAR_DIM; ++row) {
    for (dim_type col = 0; col < BOARD_DIM; ++col) {
      if (isSameColor(get(row, col), mColor)) {
        auto moves = getMoves(row, col);
        std::copy(moves.begin(), moves.end(), std::back_inserter(moveList));
      }
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// return all the positions attainable from this board
////////////////////////////////////////////////////////////////////////////////
std::vector<Board> Board::getBoards() const
{
  std::vector<Board> boardList;
  auto moveList = getMoves();

  for (auto& pm : moveList) {
    boardList.emplace_back(*this);
    boardList.back().moveRef(pm);
  }

  return boardList;
}

////////////////////////////////////////////////////////////////////////////////
// make a move on a copy of the board
////////////////////////////////////////////////////////////////////////////////
Board Board::makeMoveCopy(const PieceMove &pieceMove) const
{
  Board board(*this);
  board.makeMove(pieceMove);

  return board;
}

///////////////////////////////////////////////////////////////////////////////
// make a move on this board
///////////////////////////////////////////////////////////////////////////////
Board& Board::makeMove(const PieceMove &pieceMove)
{
  auto sq = pieceMove.fromSquare();
  auto fromCode = get(sq.row(), sq.column());

  // verify correct piece in square
  assert(isSamePiece(fromCode, sq.piece()) && isSameColor(fromCode, sq.color()));

  // fetch legal moves
  auto moveList = getMoves(sq.row(), sq.column());
  auto it = std::find(moveList.begin(), moveList.end(), pieceMove);

  // verify move is legal
  assert(it != moveList.end());

  // make the move
  moveRef(pieceMove);

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// TODO: implement undo function
////////////////////////////////////////////////////////////////////////////////
Board& Board::undo() noexcept
{
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// the count for white pieces
////////////////////////////////////////////////////////////////////////////////
PieceCount Board::whiteCount() const noexcept
{
  return mWhiteCount;
}

////////////////////////////////////////////////////////////////////////////////
// the count for black pieces
////////////////////////////////////////////////////////////////////////////////
PieceCount Board::blackCount() const noexcept
{
  return mBlackCount;
}

////////////////////////////////////////////////////////////////////////////////
// get the last move
////////////////////////////////////////////////////////////////////////////////
PieceMove Board::lastMove() const noexcept
{
  return mLastMove;
}

////////////////////////////////////////////////////////////////////////////////
// get a square from a board
////////////////////////////////////////////////////////////////////////////////
Square Board::operator()(dim_type row, dim_type column) const noexcept
{
  assert(isInBound(row, column));
  return Square(row, get(column, code));
}

////////////////////////////////////////////////////////////////////////////////
// iterator to the first square
////////////////////////////////////////////////////////////////////////////////
iterator Board::begin() const noexcept
{
  return iterator(this);
}

////////////////////////////////////////////////////////////////////////////////
// iterator to one past the last square
////////////////////////////////////////////////////////////////////////////////
iterator Board::end() const noexcept
{
  return iterator(this, int);
}

////////////////////////////////////////////////////////////////////////////////
// valid jump positions from a given row and column
////////////////////////////////////////////////////////////////////////////////
jump_list Board::jump
  (dim_type row,
   dim_type column,
   const jump_list &positions) const
{
  assert(isInBound(row, column));
  jump_list jumpList;

  for (auto& pos : positions) {
    auto toRow = row + pos.first;
    auto toCol = column + pos.second;
    if (isInBound(toRow, toColumn))
      jumpList.emplace_back(toRow, toCol);
  }

  return jumpList;
}

////////////////////////////////////////////////////////////////////////////////
// is it check from a pawn
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckPawn(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  if (isWhite(mColor)) {
    auto toRow = row+1;
    if (toRow < BOARD_DIM) {
      if (column < BOARD_DIM-1) {
        auto code = get(toRow, column+1);
        if (isPawn(code) && isBlack(code))
          return true;
      }
      if (column > 0) {
        auto code = get(toRow, column-1);
        if (isPawn(code) && isBlack(code))
          return true;
      }
    }
  } else {
    auto toRow = row-1;
    if (toRow >= 0) {
      if (column < BOARD_DIM-1) {
        auto code = get(toRow, column+1);
        if (isPawn(code) && isWhite(code))
          return true;
      }
      if (column > 0) {
        auto code = get(toRow, column-1);
        if (isPawn(code) && isWhite(code))
          return true;
      }
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is there check from a knight
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckKnight(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  auto jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto& pos : jumpList) {
    auto pcode = get(pos.first, pos.second);
    if (isKnight(pcode) && !isSameColor(pcode, mColor))
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is there a check from a bishop
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckBishop(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto piece = PieceCode::BISHOP;

  return isCheckNW(row, column, piece) || isCheckSW(row, column piece)
      || isCheckNE(row, column, piece) || isCheckSE(row, column, piece);
}

////////////////////////////////////////////////////////////////////////////////
// is there a check from a rook
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckRook(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto piece = PieceCode::ROOK;

  return isCheckN(row, column, piece) || isCheckW(row, column piece)
      || isCheckS(row, column, piece) || isCheckE(row, column, piece);
}

////////////////////////////////////////////////////////////////////////////////
// is there a check from a queen
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckQueen(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto piece = PieceCode::QUEEN;

  return isCheckN(row, column, piece) || isCheckNE(row, column, piece)
      || isCheckW(row, column, piece) || isCheckSE(row, column, piece)
      || isCheckS(row, column, piece) || isCheckSW(row, column, piece)
      || isCheckE(row, column, piece) || isCheckNW(row, column, piece);
}

////////////////////////////////////////////////////////////////////////////////
// is there a check from the king
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheckKing(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  auto jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto pcode = get(pos.first, pos.second);
    if (isKing(pcode) && !isSameColor(pcode, mColor))
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// check if king is in danger
////////////////////////////////////////////////////////////////////////////////
bool Board::isCheck(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  return isCheckRook(row, column) || isCheckBishop(row, column)
      || isCheckKing(row, column) || isCheckQueen(row, column)
      || isCheckPawn(row, column) || isCheckKnight(row, column);
}

////////////////////////////////////////////////////////////////////////////////
// check if there is an en passant at the given column
////////////////////////////////////////////////////////////////////////////////
bool
Board::isEnPassant(PieceColor color, dim_type toColumn) const noexcept
{
  if (isColorNone(color))
    return false;

  dim_type toRow, fromRow;
  if (isWhite(color)) {
    toRow = 4;
    fromRow = 6;
  } else {
    toRow = 3;
    fromRow = 1;
  }

  auto toCode = get(toRow, toColumn);
  return isPawn(toCode) && !isSameColor(toCode, mColor)
      && mLastMove.piece() == PieceCode::PAWN
      && mLastMove.fromRow() == fromRow
      && mLastMove.fromColumn() == fromColumn
      && mLastMove.toRow() == toRow
      && mLastMove.toColumn() = toColumn;
}

////////////////////////////////////////////////////////////////////////////////
// Return a list of all the pawn moves.
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::movePawn(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isPawn(fromCode));

  std::vector<PieceMove> moveList;
  dim_type cmpRow;
  std::function<bool(dim_type, dim_type)> cmpFunc;
  std::function<dim_type(dim_type, dim_type)> rowOp;

  // set handles to deal with black or white pawn move
  if (isWhite(mColor)) {
    cmpRow = 6;
    cmpFunc = std::less<dim_type>();
    rowOp = std::plus<dim_type>();
  } else {
    cmpRow = 1;
    cmpFunc = std::greater<dim_type>();
    rowOp = std::minus<dim_type>();
  }

  // all normal moves (i.e., pawn moves one square up or down)
  if (cmpFunc(row, rowCmp)) {
    auto toRow = rowOp(row, 1);
    // check one square straight up or down
    auto toCode = get(toRow, column);
    if (isPieceNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    // check one square up or down, and to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = get(toRow, toCol);
      if (!isSameColor(toCode, mColor)) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().setCapture(toRow, toCol, toCode);
      }
    }
    // check one square up or down, and to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = get(toRow, toCol);
      if (!isSameColor(toCode, mColor)) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().setCapture(toRow, toCol, toCode);
      }
    }
  }

  // set comparison row for first pawn move
  cmpRow = isWhite(mColor) ? 1 : 6;

  // two moves on first move
  if (row == cmpRow)) {
    if (isPieceNone(get(rowOp(row, 1), column)) {
      toRow = rowOp(row, 2);
      if (isPieceNone(get(toRow, column)))
        moveList.emplace_back(row, column, fromCode, toRow, column);
    }
  }

  // set comparison row for en passant
  cmpRow = isWhite(mColor) ? 5 : 4;

  // en passant
  if (row == cmpRow) {
    // checking column to the left
    if (column > 0) {
      auto toCol = column-1;
      if (isEnPassant(mColor, toCol)) {
        moveList.emplace_back(row, column, fromCode, rowOp(row, 1), toCol);
        moveList.back().setCapture(row, toCol, get(row, toCol));
      }
    }
    // checking column to the right
    if (column < 7) {
      auto toCol = column+1;
      if (isEnPassant(mColor, toCol)) {
        moveList.emplace_back(row, column, fromCode, rowOp(row, 1), toCol);
        moveList.back().setCapture(row, toCol, get(row, toCol));
      }
    }
  }

  // set comparison row for promotion
  cmpRow = isWhite(mColor) ? 6 : 1;

  // pawn promotion
  if (row == cmpRow) {
    PieceCode pcArr[] = {
      PieceCode::KNIGHT, PieceCode::BISHOP,
      PieceCode::ROOK, PieceCode::QUEEN
    };
    auto toRow = rowOp(row, 1);
    // check one square up
    auto toCode = get(toRow, column);
    if (isPieceNone(toCode)) {
      for (auto& pc : pcArr) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setPromo(toRow, column, pc, mColor);
      }
    }
    // check diagonal square to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = get(toRow, toCol);
      if (!isPieceNone(toCode) && !isSameColor(toCode, mColor)) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(toRow, toCol, toCode);
          moveList.back().setPromo(toRow, toCol, pc, mColor);
        }
      }
    }
    // check diagonal square to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = get(toRow, toCol);
      if (!isPieceNone(toCode) && !isSameColor(toCode, mColor)) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(toRow, toCol, toCode);
          moveList.back().setPromo(toRow, toCol, pc, mColor);
        }
      }
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// move knight
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::moveKnight(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isKnight(fromCode));
  std::vector<PieceMove> moveList;

  jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto &pos : jumpList) {
    auto toCode = get(pos.first, pos.second);
    if (isPieceNone(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (!isSameColor(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(pos.first, pos.second, toCode);
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// move bishop
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::moveBishop(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isBishop(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BOARD_DIM && toRow < BOARD_DIM; ++toCol, ++toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BOARD_DIM && toRow >= 0; ++toCol, --toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 && toRow < BOARD_DIM; --toCol, ++toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and down
  for (auto toCol = column-1, toRow = row-1;
       toCol >= 0 && toRow >= 0; --toCol, --toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// move rook
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::moveRook(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isRook(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().setCapture(row, toCol, toCode);
      break;
    }
  }

  // check all moves left
  for (auto toCol = column-1; toCol >= 0; --toCol) {
    auto toCode = get(row, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().setCapture(row, toCol, toCode);
      break;
    }
  }

  // check all moves up
  for (auto toRow = row+1; toRow < BOARD_DIM; ++toRow) {
    auto toCode = get(toRow, column);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  // check all moves down
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = get(toRow, column);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// move queen
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::moveQueen(dim_type row, dim_type column) const
{
  assert(!isSameColor(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isQueen(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().setCapture(row, toCol, toCode);
      break;
    }
  }

  // check all moves left
  for (auto toCol = column-1; toCol >= 0; --toCol) {
    auto toCode = get(row, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().setCapture(row, toCol, toCode);
      break;
    }
  }

  // check all moves up
  for (auto toRow = row+1; toRow < BOARD_DIM; ++toRow) {
    auto toCode = get(toRow, column);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  // check all moves down
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = get(toRow, column);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BOARD_DIM && toRow < BOARD_DIM; ++toCol, ++toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BOARD_DIM && toRow >= 0; ++toCol, --toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 && toRow < BOARD_DIM; --toCol, ++toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and down
  for (auto toCol = column-1, toRow = row-1;
       toCol >= 0 && toRow >= 0; --toCol, --toRow) {
    auto toCode = get(toRow, toCol);
    if (isSameColor(toCode, mColor))
      break;
    else if (isColorNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// move king
////////////////////////////////////////////////////////////////////////////////
std::vector<PieceMove>
Board::moveKing(dim_type row, dim_type column) const
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto fromCode = get(row, column);
  assert(isKing(fromCode));
  std::vector<PieceMove> moveList;

  // normal moves
  jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto toCode = get(pos.first, pos.second);
    if (isPieceNone(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (!isSameColor(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(pos.first, pos.second, toCode);
    }
  }

  // short castling
  if (canCastle()) {
    moveList.emplace_back();
    moveList.back().doCastle();
  }

  // long castling
  if (canCastleLong()) {
    moveList.emplace_back();
    moveList.back().doCastleLong();
  }

  return moveList;
}

////////////////////////////////////////////////////////////////////////////////
// get a copy of the board after making a move
////////////////////////////////////////////////////////////////////////////////
Board Board::moveCopy(const PieceMove &pieceMove) const
{
  Board board(*this);
  board.moveRef(pieceMove);
  return board;
}

////////////////////////////////////////////////////////////////////////////////
// make a move on this board
////////////////////////////////////////////////////////////////////////////////
Board& Board::moveRef(const PieceMove &pieceMove) noexcept
{
  assert(!isColorNone(mColor));

  // clear piece from where it is moving
  clearSq(pieceMove.fromRow(), pieceMove.fromColumn());

  // clear captured piece and adjust piece count
  if (pieceMove.isCapture()) {
    clearSq(pieceMove.captureRow(), pieceMove.captureColumn());
    auto& pc = isWhite(mColor) ? mBlackCount : mWhiteCount;
    pc -= pieceMove.capturePiece();
    // check if it is mate
    if (isKing(pieceMove.capturePiece())
      mBoardInfo.set(isWhite(mColor) ? BK_MATE : WK_MATE);
  }

  auto piece = pieceMove.fromPiece();
  if (isPawn(piece)) {
    if (!pieceMove.isPromo()) {
      put(pieceMove.toRow(), pieceMove.toColumn(), PieceMove::PAWN);
    else {
      put(pieceMove.toRow(), pieceMove.toColumn(), pieceMove.promoPiece());
      // adjust piece count
      auto& pc = isWhite(mColor) ? mWhiteCount : mBlackCount;
      pc -= PieceCode::PAWN;
      pc += pieceMove.promoPiece();
    }
  } else if (isKing(piece)) {
    if (!pieceMove.isCastle() && !pieceMove.isCastleLong())
      put(pieceMove.toRow(), pieceMove.toColumn(), PieceCode::KING);
    else if (pieceMove.isCastle()) {
      auto row = isWhite(mColor) ? 0 : 7;
      // clear the rook from corner square
      clearSq(row, 7);
      put(row, 6, PieceCode::KING);
      put(row, 5, PieceCode::ROOK);
      // note that rook in h column has moved
      mBoardInfo.set(isWhite(mColor) ? RK_H1_MOVED : RK_H8_MOVED);
    } else {  // is long castling
      auto row = isWhite(mColor) ? 0 : 7;
      // clear the rook from corner square
      clearSq(row, 0);
      put(row, 2, PieceCode::KING);
      put(row, 3, PieceCode::ROOK);
      // note that rook in a column has moved
      mBoardInfo.set(isWhite(mColor) ? RK_A1_MOVED : RK_A8_MOVED);
    }
    mBoardInfo.set(isWhite(mColor) ? WK_MOVED : BK_MOVED);
  } else {
    put(pieceMove.toRow(), pieceMove.toColumn(), piece);
    // have any of the rooks moved
    if (isRook(piece)) {
      auto row = pieceMove.fromRow();
      auto col = pieceMove.fromColumn();
      if (isWhite(mColor)) {
        if (!mBoardInfo[RK_A8_MOVED] && row == 0 && column == 7)
          mBoardInfo.set(RK_A8_MOVED);
        else if (!mBoardInfo[RK_A1_MOVED] && row == 0 && column == 0)
          mBoardInfo.set(RK_A1_MOVED);
      } else {
        if (!mBoardInfo[RK_H8_MOVED] && row == 7 && column == 7)
          mBoardInfo.set(RK_H8_MOVED);
        else if (!mBoardInfo[RK_H1_MOVED] && row == 7 && column == 0)
          mBoardInfo.set(RK_H1_MOVED);
      }
    }
  }

  // update the last move
  mLastMove = pieceMove;

  // flip color's turn
  mColor = ~mColor;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// is there a check in the diagonal from above and to the right
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckNE(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  for (auto toRow = row+1, toCol = column+1;
       toRow < BOARD_DIM && toCol < BOARD_DIM; ++toRow, ++toCol) {
    auto toCode = get(toRow, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is there a check in the diagonal from below and to the right
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckSE(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  for (auto toRow = row-1, toCol = column+1;
       toRow >= 0 && toCol < BOARD_DIM; --toRow, ++toCol) {
    auto toCode = get(toRow, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is there a check in the diagonal from below and to the left
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckSW(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  for (auto toRow = row-1, toCol = column-1;
       toRow >= 0 && toCol >= 0; --toRow, --toCol) {
    auto toCode = get(toRow, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is there a check in the diagonal from above and to the left
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckNW(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  for (auto toRow = row+1, toCol = column-1;
       toRow < BOARD_DIM && toCol >= 0; ++toRow, --toCol) {
    auto toCode = get(toRow, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is it check in column from above
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckN(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  // check against piece in colomn from above
  for (auto toRow = row+1; toRow < BOARD_DIM; ++toRow) {
    auto toCode = get(toRow, column);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is it check in row from right
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckE(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  // check against piece in row from the right
  for (auto toCol = row+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is it check in column from below
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckS(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  // check against piece in column from below
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = get(toRow, column);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// is it check in row from left
////////////////////////////////////////////////////////////////////////////////
bool
Board::isCheckW(dim_type row, dim_type column, PieceCode piece) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

  // check against piece in row from left
  for (auto toCol = row-1; toCol >= 0; --toCol) {
    auto toCode = get(row, toCol);
    if (isColorNone(toCode))
      continue;
    else if (isSameColor(toCode, mColor) || !isSamePiece(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// get the piece code on a squre
////////////////////////////////////////////////////////////////////////////////
inline piececode_t Board::get(dim_type row, dim_type column) const noexcept
{
  assert(isInBound(row, column));
  return mRows[row][column];
}

////////////////////////////////////////////////////////////////////////////////
// get the piece code on a squre
////////////////////////////////////////////////////////////////////////////////
inline void Board::put(dim_type row, dim_type column, piececode_t code) noexcept
{
  assert(isInBound(row, column));
  mRows[row][column] = code;
}

////////////////////////////////////////////////////////////////////////////////
// TODO: implement output operator for Board
////////////////////////////////////////////////////////////////////////////////
std:ostream& operator<<(std:ostream &os, const Board &board)
{
  return os;
}

////////////////////////////////////////////////////////////////////////////////
// compare boards for equality
////////////////////////////////////////////////////////////////////////////////
bool operator==(const Board &boar1, const Board &board2) noexcept
{
  return board1.mColor == board2.mColor
      && std::equal(board1.begin(), board1.end(), board2.begin());
}

////////////////////////////////////////////////////////////////////////////////
// compare boards for non-equality
////////////////////////////////////////////////////////////////////////////////
bool operator!=(const Board &boar1, const Board &board2) noexcept
{
  return !(board1 == board2);
}

// BoardIterator

////////////////////////////////////////////////////////////////////////////////
// ctor to beginning of board
////////////////////////////////////////////////////////////////////////////////
BoardIterator::BoardIterator(const Board &board)
  : mBoard(board),
    mIndex(0),
    mCode(mBoard.get(0, 0)) {}

////////////////////////////////////////////////////////////////////////////////
// ctor to end of board
////////////////////////////////////////////////////////////////////////////////
BoardIterator::BoardIterator(const Board &board, int)
  : mBoard(board),
    mIndex(LAST_INDEX),
    mCode(0) {}

////////////////////////////////////////////////////////////////////////////////
// prefix increment operator
////////////////////////////////////////////////////////////////////////////////
BoardIterator& BoardIterator::operator++()
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  ++mIndex;
  mCode = mIndex == LAST_INDEX ? 0 : mBoard.get(row(), column());

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// postfix increment operator
////////////////////////////////////////////////////////////////////////////////
BoardIterator BoardIterator::operator++(int)
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  BoardIterator bi(*this);
  ++*this;

  return bi;
}

////////////////////////////////////////////////////////////////////////////////
// increment and assignment operator
////////////////////////////////////////////////////////////////////////////////
BoardIterator&
BoardIterator::operator+=(BoardIterator::difference_type value)
{
  auto tmp = mIndex + value;
  if (tmp < 0 || tmp > LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  mIndex = tmp;
  mCode = mIndex == LAST_INDEX ? 0 : mBoard.get(row(), colum());

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// decrement and assignment operator
////////////////////////////////////////////////////////////////////////////////
BoardIterator&
BoardIterator::operator-=(BoardIterator::difference_type value)
{
  auto tmp = mIndex - value;
  if (tmp < 0 || tmp >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  mIndex = tmp;
  mCode = mIndex == LAST_INDEX ? 0 : mBoard.get(row(), column());

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// dereference operator
////////////////////////////////////////////////////////////////////////////////
BoardIterator::value_type BoardIterator::operator*() const
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  return mCode;
}

////////////////////////////////////////////////////////////////////////////////
// get the piece on the current square
////////////////////////////////////////////////////////////////////////////////
PieceCode BoardIterator::piece() const noexcept
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  return getPieceCode(mCode);
}

////////////////////////////////////////////////////////////////////////////////
// get the color of the piece on the current square
////////////////////////////////////////////////////////////////////////////////
PieceColor BoardIterator::color() const
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  return getPieceColor(mCode);
}

////////////////////////////////////////////////////////////////////////////////
// get the row of the current square
////////////////////////////////////////////////////////////////////////////////
BoardIterator::dim_type BoardIterator::row() const
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  return mIndex >> 3;
}

////////////////////////////////////////////////////////////////////////////////
// get the column of the current square
////////////////////////////////////////////////////////////////////////////////
BoardIterator::dim_type BoardIterator::column() const
{
  if (mIndex >= LAST_INDEX)
    throw ChessError("Iterator cannot move beyond board");

  return mIndex & (Board::BOARD_DIM-1);
}

////////////////////////////////////////////////////////////////////////////////
// compare two board iterators for equality
////////////////////////////////////////////////////////////////////////////////
bool
operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return &bi1.mBoard == &bi2.mBoard && bi1.mIndex == bi2.mIndex;
}

////////////////////////////////////////////////////////////////////////////////
// compare two board iterators for non-equality
////////////////////////////////////////////////////////////////////////////////
bool
operator!=(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return !(bi1 == bi2);
}

////////////////////////////////////////////////////////////////////////////////
// get the difference between two iterators
////////////////////////////////////////////////////////////////////////////////
BoardIterator::difference_type
operator-(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return bi1.mIndex - bi2.mIndex;
}

////////////////////////////////////////////////////////////////////////////////
// get the iterator obtained by subtracting an integral value
////////////////////////////////////////////////////////////////////////////////
BoardIterator
operator-(const BoardIterator &bi, BoardIterator::difference_type value)
{
  BoardIterator newBi(bi);
  newBi -= value;
  return newBi;
}

////////////////////////////////////////////////////////////////////////////////
// get the iterator obtained by adding an integral value
////////////////////////////////////////////////////////////////////////////////
BoardIterator
operator+(const BoardIterator &bi, BoardIterator::difference_type value)
{
  BoardIterator newBi(bi);
  newBi += value;
  return newBi;
}

} // namespace zoor
