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

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemove.hh"
#include "board.hh"

namespace zoor {

// aliases
using dim_type = Board::dim_type;
using jump_list = Board::jump_list;

// initialize JUMP_KNIGHT
const jump_list Board::JUMP_KNIGHT = {
  {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
  {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

// initialize JUMP_KING
const jump_list Board::JUMP_KING = {
  {1, 0}, {1, 1}, {0, 1}, {-1, 1},
  {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};

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

// get all the moves from all the pieces
std::vector<PieceMove> Board::getMoves() const
{
  assert(!isColorNone(mColor));

  std::vector<PieceMove> moves, moveList;

  for (dim_type i = 0; i < BOAR_DIM; ++i) {
    for (dim_type j = 0; j < BOARD_DIM; ++j) {

      auto code = get(i, j);

      if (isPieceNone(code) || !isSameColor(code, mColor))
        continue;

      switch (getPieceCode(code)) {
      case PieceCode::PAWN:
        moves = movePawn(i, j);
        break;
      case PieceCode::KNIGHT:
        moves = moveKnight(i, j);
        break;
      case PieceCode::BISHOP:
        moves = moveBishop(i, j);
        break;
      case PieceCode::ROOK:
        moves = moveRook(i, j);
        break;
      case PieceCode::QUEEN:
        moves = moveQueen(i, j);
        break;
      case PieceCode::KING:
        moves = moveKing(i, j);
        break;
      default:
        // should never get here
        assert(false);
        break;
      }

      std::copy(moves.begin(), moves.end(), std::back_inserter(moveList));
    }
  }

  return moveList;
}

// check if king can do short castling
bool Board::canCastle() const noexcept
{
  dim_type row;
  decltype(mBoardInfo) shift;

  // row and shift parameter for color
  if (isWhite(mColor)) {
    row = 0;
    shift = 0;
  } else {
    row = 7;
    shift = 4;
  }

  // check conditions
  // 1. rook a1 or a8 has not moved
  // 2. king has not moved
  // 3. king is not in check
  auto cond = (mBoardInfo >> shift) & 1U;
  shift += 2;
  cond |= (mBoardInfo >> shift) & 1U;
  cond |= (mBoardInfo >> ++shift) & 1U;

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

// check if king can do long castling
bool Board::canCastleLong() const noexcept
{
  dim_type row;
  decltype(mBoardInfo) shift;

  // row and shift parameter for color
  if (isWhite(mColor)) {
    row = 1;
    shift = 1;
  } else {
    row = 7;
    shift = 5;
  }

  // check conditions
  // 1. rook h1 or h8 has not moved
  // 2. king has not moved
  // 3. king is not in check
  auto cond = (mBoardInfo >> shift) & 1U;
  cond |= (mBoardInfo >> ++shift) & 1U;
  cond |= (mBoardInfo >> ++shift) & 1U;

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

/**
 * TODO: implement moveCopy
 */
Board
Board::moveCopy(const PieceMove &pieceMove) const
{
  return Board();
}

/**
 * TODO: implement moveRef
 */
Board&
Board::moveRef(const PieceMove &pieceMove) noexcept
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

// is there a check in the diagonal from above and to the right
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

// is there a check in the diagonal from below and to the right
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

// is there a check in the diagonal from below and to the left
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

// is there a check in the diagonal from above and to the left
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

// is it check in column from above
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

// is it check in row from right
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

// is it check in column from below
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

// is it check in row from left
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

// is it check from a pawn
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

// is there check from a knight
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

// is there a check from a bishop
bool Board::isCheckBishop(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto piece = PieceCode::BISHOP;

  return isCheckNW(row, column, piece) || isCheckSW(row, column piece)
      || isCheckNE(row, column, piece) || isCheckSE(row, column, piece);
}

// is there a check from a rook
bool Board::isCheckRook(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));
  auto piece = PieceCode::ROOK;

  return isCheckN(row, column, piece) || isCheckW(row, column piece)
      || isCheckS(row, column, piece) || isCheckE(row, column, piece);
}

// is there a check from a queen
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

// is there a check from the king
bool Board::isCheckKing(dim_type row, dim_type column) const noexcept
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

// check if king is in danger
bool Board::isCheck(dim_type row, dim_type column) const noexcept
{
  assert(!isColorNone(mColor));
  assert(isInBound(row, column));

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
  return isPawn(toCode) && !isSameColor(toCode, mColor)
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
  if (row == cmpRow) {
    auto toRow = rowOp(row, 2);
    auto toCode = get(toRow, column);
    if (isPieceNone(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
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

// move knight
std::vector<PieceMove>
Board::moveKnight(dim_type row, dim_type column) const noexcept
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

// move bishop
std::vector<PieceMove>
Board::moveBishop(dim_type row, dim_type column) const noexcept
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

// move rook
std::vector<PieceMove>
Board::moveRook(dim_type row, dim_type column) const noexcept
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

// move queen
std::vector<PieceMove>
Board::moveQueen(dim_type row, dim_type column) const noexcept
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

// move king
std::vector<PieceMove>
Board::moveKing(dim_type row, dim_type column) const noexcept
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
  assert(isInBound(row, column));
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
  return Square(row, col, code);
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
