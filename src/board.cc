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

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemove.hh"
#include "board.hh"

namespace zoor {

using dim_type = Board::dim_type;

/**
 * TODO: determine how to initialize default board.
 */
Board::Board() {}

const std:array<row_type, Board::BOARD_DIM>&
Board::rows() const noexcept
{
  return mRows;
}

std:array<row_type, Board::BOARD_DIM>
Board::rowsCopy() const
{
  auto rc(mRows);
  return rc;
}

/**
 * TODO: implement getMoves function
 */
std::vector<PieceMove> Board::getMoves() const noexcept
{
  return std::vector<PieceMove>();
}

/**
 * TODO: implement moveCopy
 */
Board
Board::moveCopy(const Square &square1, const Square &square2) const noexcept
{
  return Board();
}

/**
 * TODO: implement moveRef
 */
Board&
Board::moveRef(const Square &square1, const Square &square2) noexcept
{
  return *this;
}

// check if position is valid in board
bool Board::isInBound(dim_type position) const noexcept
{
  return position >= 0 && position < BOARD_DIM;
}

// check if row and column are within bounds of board
bool Board::isInBound(dim_type row, dim_type column) const noexcept
{
  return row >= 0 && column < BOARD_DIM
      && column >= 0 && column < BOARD_DIM;
}

// valid jump positions from a given row and column
jump_list Board::jump
  (dim_type row,
   dim_type column,
   const jump_list &positions) const noexcept
{
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  jump_list jumpList;

  for (auto& pos : positions) {
    auto toRow = row + pos.first;
    auto toCol = column + pos.second;
    if (isInBound(toRow, toColumn))
      jumpList.emplace_back(toRow, toCol);
  }

  return jumpList;
}

// TODO: implement
bool Board::isCheckPawn(dim_type row, dim_type column) const noexcept
{
  return false;
}

// TODO: implement
bool Board::isCheckKnight(dim_type row, dim_type column) const noexcept
{
  return false;
}

// TODO: implement
bool Board::isCheckBishop(dim_type row, dim_type column) const noexcept
{
  return false;
}

// TODO: implement
bool Board::isCheckRook(dim_type row, dim_type column) const noexcept
{
  return false;
}

// is there a check from a rook
bool Board::isCheckRook(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);

  // check against rook above
  for (auto toRow = row+1; toRow < BOARD_DIM; ++toRow) {
    auto toCode = get(toRow, column);
    auto color = getPieceColor(toCode);
    if (color == PieceColor::NONE)
      continue;
    else if (color == mColor || getPieceCode(toCode) != PieceCode::ROOK)
      break;
    else
      return true;
  }

  // check against rook below
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = get(toRow, column);
    auto color = getPieceColor(toCode);
    if (color == PieceColor::NONE)
      continue;
    else if (color == mColor || getPieceCode(toCode) != PieceCode::ROOK)
      break;
    else
      return true;
  }

  // check against rook to the right
  for (auto toCol = col+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    auto color = getPieceColor(toCode);
    if (color == PieceColor::NONE)
      continue;
    else if (color == mColor || getPieceCode(toCode) != PieceCode::ROOK)
      break;
    else
      return true;
  }

  // check against rook to the left
  for (auto toCol = col-1; toCol >= 0; --toCol) {
    auto toCode = get(row, toCol);
    auto color = getPieceColor(toCode);
    if (color == PieceColor::NONE)
      continue;
    else if (color == mColor || getPieceCode(toCode) != PieceCode::ROOK)
      break;
    else
      return true;
  }

  return false;
}

// check if king is in danger
bool Board::isCheck(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);

  return isCheckRook(row, column) || isCheckBishop(row, column)
      || isCheckKing(row, column) || isCheckQueen(row, column)
      || isCheckPawn(row, column) || isCheckKnight(row, column);
}

// check if there is an en passant at the given column
bool
Board::isEnPassant(PieceColor color, dim_type toColumn) const noexcept
{
  if (color == PieceColor::NONE)
    return false;

  dim_type toRow, fromRow;
  if (color == PieceColor::WHITE) {
    toRow = 4;
    fromRow = 6;
  } else {
    toRow = 3;
    fromRow = 1;
  }

  auto toCode = get(toRow, toColumn);
  return getPieceCode(toCode) == PieceCode::PAWN
      && getPieceColor(toCode) != mColor
      && mLastMove.piece() == PieceCode::PAWN
      && mLastMove.fromRow() == fromRow
      && mLastMove.fromColumn() == toColumn
      && mLastMove.toRow() == toRow
      && mLastMove.toColumn() = toColumn;
}

// Return a list of all the pawn moves.
std::vector<PieceMove>
Board::movePawn(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::PAWN);

  std::vector<PieceMove> moveList;
  dim_type cmpRow;
  std::function<bool(dim_type, dim_type)> cmpFunc;
  std::function<dim_type(dim_type, dim_type)> rowOp;

  // set handles to deal with black or white pawn move
  if (mColor == PieceColor::WHITE) {
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
    if (getPieceCode(toCode) == PieceCode::NONE)
      moveList.emplace_back(row, column, fromCode, toRow, column);
    // check one square up or down, and to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = get(toRow, toCol);
      if (getPieceColor(toCode) != PieceColor::WHITE) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().setCapture(toRow, toCol, toCode);
      }
    }
    // check one square up or down, and to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = get(toRow, toCol);
      if (getPieceColor(toCode) != PieceColor::WHITE) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().setCapture(toRow, toCol, toCode);
      }
    }
  }

  // set comparison row for first pawn move
  cmpRow = mColor == PieceColor::WHITE ? 1 : 6;

  // two moves on first move
  if (row == cmpRow) {
    auto toRow = rowOp(row, 2);
    auto toCode = get(toRow, column);
    if (getPieceCode(toCode) == PieceCode::NONE)
      moveList.emplace_back(row, column, fromCode, toRow, column);
  }

  // set comparison row for en passant
  cmpRow = mColor == PieceColor::WHITE ? 5 : 4;

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
  cmpRow = mColor == PieceColor::WHITE ? 6 : 1;

  // pawn promotion
  if (row == cmpRow) {
    PieceCode pcArr[] = {
      PieceCode::KNIGHT, PieceCode::BISHOP,
      PieceCode::ROOK, PieceCode::QUEEN
    };
    auto toRow = rowOp(row, 1);
    // check one square up
    auto toCode = get(toRow, column);
    if (getPieceCode(toCode) == PieceCode::NONE) {
      for (auto& pc : pcArr) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setPromotion(toRow, column, pc, mColor);
      }
    }
    // check diagonal square to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = get(toRow, toCol);
      if (getPieceCode(toCode) != PieceCode::NONE
          && getPieceColor(toCode) != mColor) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(toRow, toCol, toCode);
          moveList.back().setPromotion(toRow, toCol, pc, mColor);
        }
      }
    }
    // check diagonal square to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = get(toRow, toCol);
      if (getPieceCode(toCode) != PieceCode::NONE
          && getPieceColor(toCode) != mColor) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(toRow, toCol, toCode);
          moveList.back().setPromotion(toRow, toCol, pc, mColor);
        }
      }
    }
  }

  return moveList;
}

// move knight
std::vector<PieceMove>
Board::moveKnight(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::KNIGHT);
  std::vector<PieceMove> moveList;

  // move deltas for row and column
  jump_list jumpList = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
  };

  jumpList = jump(row, column, jumpList);
  for (auto &pos : jumpList) {
    auto toCode = get(pos.first, pos.second);
    if (getPieceCode(toCode) == PieceCode::NONE)
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (getPieceColor(toCode) != mColor) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(pos.first, pos.second, toCode);
    }
  }

  return moveList;
}

// move bishop
std::vector<PieceMove>
Board::moveBishop(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::BISHOP);
  std::vector<PieceMove> moveList;

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BOARD_DIM && toRow < BOARD_DIM; ++toCol, ++toRow) {
    auto toCode = get(toRow, toCol);
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

// move rook
std::vector<PieceMove>
Board::moveRook(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::ROOK);
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE) {
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  return moveList;
}

// move queen
std::vector<PieceMove>
Board::moveQueen(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::QUEEN);
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BOARD_DIM; ++toCol) {
    auto toCode = get(row, toCol);
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE) {
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
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
    auto toColor = getPieceColor(toCode);
    if (toColor == mColor)
      break;
    else if (toColor == PieceColor::NONE)
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

// move king
std::vector<PieceMove>
Board::moveKing(dim_type row, dim_type column) const noexcept
{
  assert(mColor != PieceColor::NONE);
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  auto fromCode = get(row, column);
  assert(getPieceCode(fromCode) == PieceCode::KING);
  std::vector<PieceMove> moveList;

  // move deltas for row and column
  jump_list jumpList = {
    {1, 0}, {1, 1}, {0, 1}, {-1, 1},
    {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
  };

  jumpList = jump(row, column, jumpList);
  for (auto& pos : jumpList) {
    auto toCode = get(pos.first, pos.second);
    if (getPieceCode(toCode) == PieceCode::NONE)
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (getPieceColor(toCode) != mColor) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(pos.first, pos.second, toCode);
    }
  }

  /* TODO: implement castling
   * have to check if we are on check, or if any of the squres through which the
   * king has to pass would put him on check, and if the king has moved, or if
   * the rook has moved
   */

  return moveList;
}

/**
 * TODO: implement getBoardsFromMoves function
 */
std::vector<Board>
Board::getBoardsFromMoves() const noexcept
{
  return std::vector<Board>();
}

/**
 * TODO: implement makeMoveCopy function
 */
Board
Board::makeMoveCopy(const Square &square1, const Square &square2) const noexcept
{
  return Board();
}

/**
 * TODO: implement makeMove function
 */
Board&
Board::makeMove(const Square &square1, const Square &square2) noexcept
{
  return *this;
}

/**
 * TODO: implement undo function
 */
Board& Board::undo() noexcept
{
  return *this;
}

// the count for white pieces
PieceCount Board::whiteCount() const noexcept
{
  return mWhiteCount;
}

// the count for black pieces
PieceCount Board::blackCount() const noexcept
{
  return mBlackCount;
}

// get the last move
PieceMove Board::lastMove() const noexcept
{
  return mLastMove;
}

// get a square from a board
Square Board::operator()(dim_type row, dim_type column) const noexcept
{
  assert(row >= 0 && row < BOARD_DIM);
  assert(column >= 0 && column < BOARD_DIM);
  return Square(row, get(column, code));
}

iterator Board::begin() const noexcept
{
  return iterator(this);
}

iterator Board::end() const noexcept
{
  return iterator(this, int);
}

/**
 * TODO: implement output operator for Board
 */
std:ostream& operator<<(std:ostream &os, const Board &board)
{
  return os;
}

bool operator==(const Board &boar1, const Board &board2) noexcept
{
  return board1.mColor == board2.mColor
      && std::equal(board1.begin(), board1.end(), board2.begin());
}

bool operator!=(const Board &boar1, const Board &board2) noexcept
{
  return !(board1 == board2);
}

// BoardIterator

BoardIterator::BoardIterator(const Board *board)
  : mBoardPtr(board),
    mIndex(0)
{
  assert(mBoardPtr != nullptr);
}

BoardIterator::BoardIterator(const Board *board, int)
  : mBoardPtr(board),
    mIndex(LAST_INDEX)
{
  assert(mBoardPtr != nullptr);
}

BoardIterator& BoardIterator::operator++()
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  ++mIndex;
  return *this;
}

BoardIterator BoardIterator::operator++(int)
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  BoardIterator bi(*this);
  ++(*this);
  return bi;
}

BoardIterator&
BoardIterator::operator+=(BoardIterator::difference_type value)
{
  mIndex += value;
  if (mIndex < static_cast<difference_type>(0)
      || mIndex > static_cast<difference_type>(LAST_INDEX))
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  return *this;
}

BoardIterator&
BoardIterator::operator-=(BoardIterator::difference_type value)
{
  mIndex -= value;
  if (mIndex < static_cast<difference_type>(0)
      || mIndex > static_cast<difference_type>(LAST_INDEX))
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  return *this;
}

BoardIterator::value_type BoardIterator::operator*() const
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: cannot access square beyond board");

  auto row = static_cast<Board::dim_type>(mIndex) / Board::BOARD_DIM;
  auto col = static_cast<Board::dim_type>(mIndex) % Board::BOARD_DIM;
  auto code = mBoardPtr->get(row, col);
  return Square(row, col, getPieceCode(pcode), getPieceColor(pcode));
}

bool
operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return bi1.mBoardPtr == bi2.mBoardPtr && bi1.mIndex == bi2.mIndex;
}

bool
operator!=(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return !(bi1 == bi2);
}

BoardIterator::difference_type
operator-(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return bi1.mIndex - bi2.mIndex;
}

BoardIterator
operator-(const BoardIterator &bi, BoardIterator::difference_type value)
{
  BoardIterator newBi(bi);
  newBi -= value;
  return newBi;
}

BoardIterator
operator+(const BoardIterator &bi, BoardIterator::difference_type value)
{
  BoardIterator newBi(bi);
  newBi += value;
  return newBi;
}

} // namespace zoor
