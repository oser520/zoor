////////////////////////////////////////////////////////////////////////////////
//! @file board.cc
//! @author Omar A Serrano
//! @date 2015-12-26
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <cassert>
#include <functional>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

//
// zoor
//
#include "basicboard.hh"
#include "basictypes.hh"
#include "board.hh"
#include "chesserror.hh"
#include "piecemove.hh"
#include "square.hh"

namespace zoor {

//
// aliases
//
using jump_list = Board::jump_list;

//
// initialize static vars
//
const jump_list Board::JUMP_KNIGHT = {
  {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
  {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

const jump_list Board::JUMP_KING = {
  {1, 0}, {1, 1}, {0, 1}, {-1, 1},
  {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};

////////////////////////////////////////////////////////////////////////////////
// Board
////////////////////////////////////////////////////////////////////////////////

//
// default ctor
//
Board::Board()
  : mColor(Color::W) {}

//
// constructor with list of pieces
//
Board::Board(
  const std::vector<Square> &squareList,
  const Color color,
  const BoardInfo &boardInfo,
  const PieceMove &lastMove)
  : mBoard(BasicBoard::emptyBoard()),
    mColor(color),
    mLastMove(lastMove),
    mInfo(boardInfo)
{
  assert(not notColor(mColor));
  assert(not squareList.empty());

  for (auto& sq : squareList)
    mBoard.put(sq.row(), sq.column(), sq.code());

  if (not isLastMoveOk())
    throw ChessError("Bad last move");
}

//
// check if king can do short castling
//
bool
Board::canCastle() const noexcept
{
  dim_t row;

  // set row to first or last
  if (isWhite(mColor)) {
    if (not mInfo.wkCastle())
      return false;
    row = 0;
  } else {
    if (not mInfo.bkCastle())
      return false;
    row = 7;
  }

  // check that king is in castling position
  auto piece = mBoard.get(row, 4);
  if (not isKing(piece) or not isSame(piece, mColor))
    return false;

  // check that rook is in castling position
  piece = mBoard.get(row, 7);
  if (not isRook(piece) or not isSame(piece, mColor))
    return false;

  // path for castling is clear
  if (not notPiece(mBoard.get(row, 5)) or not notPiece(mBoard.get(row, 6)))
    return false;

  // no checks
  if (isCheck(row, 4) or isCheck(row, 5) or isCheck(row, 6))
    return false;

  return true;
}

//
// check if king can do long castling
//
bool
Board::canCastleLong() const noexcept
{
  dim_t row;

  // row and shift parameter for color
  if (isWhite(mColor)) {
    if (not mInfo.wkCastleLong())
      return false;
    row = 0;
  } else {
    if (not mInfo.bkCastleLong())
      return false;
    row = 7;
  }

  // check that king is in castling position
  auto piece = mBoard.get(row, 4);
  if (not isKing(piece) or not isSame(piece, mColor))
    return false;

  // check that rook is in castling position
  piece = mBoard.get(row, 0);
  if (not isRook(piece) or not isSame(piece, mColor))
    return false;

  // path for castling is clear
  if (not notPiece(mBoard.get(row, 3)) or not notPiece(mBoard.get(row, 2)))
    return false;

  // no checks on path to castle
  if (isCheck(row, 3) or isCheck(row, 2))
    return false;

  // not in check now
  if (isCheck(row, 4))
    return false;

  return true;
}

//
// get the moves that can be made from a given square
//
std::vector<PieceMove>
Board::getMoves(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  std::vector<PieceMove> moveList;

  auto code = mBoard.get(row, column);

  if (notPiece(code) or not isSame(code, mColor))
    return moveList;

  switch (getPiece(code)) {
  case Piece::P:
    moveList = movePawn(row, column);
    break;
  case Piece::N:
    moveList = moveKnight(row, column);
    break;
  case Piece::B:
    moveList = moveBishop(row, column);
    break;
  case Piece::R:
    moveList = moveRook(row, column);
    break;
  case Piece::Q:
    moveList = moveQueen(row, column);
    break;
  case Piece::K:
    moveList = moveKing(row, column);
    break;
  default:
    break;
  }

  return moveList;
}

//
// get all the moves from all the pieces
//
std::vector<PieceMove>
Board::getMoves() const
{
  assert(not notColor(mColor));

  std::vector<PieceMove> moveList;

  for (dim_t row = 0; row < BasicBoard::DIM; ++row) {
    for (dim_t col = 0; col < BasicBoard::DIM; ++col) {
      if (isSame(mBoard.get(row, col), mColor)) {
        auto moves = getMoves(row, col);
        std::copy(moves.begin(), moves.end(), std::back_inserter(moveList));
      }
    }
  }

  return moveList;
}

//
// return all the positions attainable from this board
//
std::vector<Board>
Board::getBoards() const
{
  std::vector<Board> boardList;
  auto moveList = getMoves();

  // copy this board and make a move
  for (auto& pm : moveList) {
    boardList.emplace_back(*this);
    boardList.back().moveRef(pm);
  }

  return boardList;
}

//
// make a move on this board
//
Board&
Board::makeMove(const PieceMove &pMove)
{
  auto r = pMove.sRow();
  auto c = pMove.sColumn();
  auto pc = mBoard.get(r, c);

  // verify correct piece in square
  assert(isSame(pc, pMove.sPiece()) and isSame(pc, pMove.sColor()));

  // fetch legal moves
  auto moveList = getMoves(r, c);
  auto it = std::find(moveList.begin(), moveList.end(), pMove);

  // throw error if move not legal
  if (it == moveList.end())
    throw ChessError("Illegal move");

  // make the move
  moveRef(pMove);

  return *this;
}

//
// check if the last move is valid, given the current position on the board
//
bool
Board::isLastMoveOk() const noexcept
{
  auto piece = mLastMove.sPiece();
  if (not notPiece(piece)) {
    // check that there is no piece from square where piece moved from
    if (not notPiece(mBoard.get(mLastMove.sRow(), mLastMove.sColumn())))
      return false;

    if (mLastMove.isCastle()) {
      if (isWhite(mLastMove.sColor())) {
        auto pcode = mBoard.get(0, 7);
        if (not isRook(pcode) or not isWhite(pcode))
          return false;
        pcode = mBoard.get(0, 4);
        if (not isKing(pcode) or not isWhite(pcode))
          return false;
        // check if board info allows castling
        if (not mInfo.wkCastle())
          return false;
      } else {
        auto pcode = mBoard.get(7, 7);
        if (not isRook(pcode) or not isBlack(pcode))
          return false;
        pcode = mBoard.get(7, 4);
        if (not isKing(pcode) or not isBlack(pcode))
          return false;
        // check if board info allows castling
        if (not mInfo.bkCastle())
          return false;
      }
    } else if (mLastMove.isCastleLong()) {
      if (isWhite(mLastMove.sColor())) {
        auto pcode = mBoard.get(0, 0);
        if (not isRook(pcode) or not isWhite(pcode))
          return false;
        pcode = mBoard.get(0, 2);
        if (not isKing(pcode) or not isWhite(pcode))
          return false;
        // check if board info allows castling
        if (not mInfo.wkCastleLong())
          return false;
      } else {
        auto pcode = mBoard.get(7, 0);
        if (not isRook(pcode) or not isBlack(pcode))
          return false;
        pcode = mBoard.get(7, 2);
        if (not isKing(pcode) or not isBlack(pcode))
          return false;
        // check if board info allows castling
        if (not mInfo.bkCastleLong())
          return false;
      }
    } else if (mLastMove.isPromo()) {
      auto pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      auto ppromo = mLastMove.dPiece();
      if (not isSame(pcode, ppromo) or not isSame(pcode, pcolor))
        return false;
    } else if (mLastMove.isEnPassant()) {
      // check there's no piece at capture square
      auto pcode = mBoard.get(mLastMove.xRow(), mLastMove.xColumn());
      if (not notPiece(pcode))
        return false;
      pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      if (not isPawn(pcode) or not isSame(pcode, pcolor))
        return false;
    } else {
      auto pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      if (not isSame(pcode, piece) or not isSame(pcode, pcolor))
        return false;
    }
  }

  return true;
}

//
// valid jump positions from a given row and column
//
jump_list Board::jump
  (dim_t row,
   dim_t column,
   const jump_list &positions) const
{
  assert(BasicBoard::inBoard(row, column));
  jump_list jumpList;

  for (auto& pos : positions) {
    auto toRow = row + pos.first;
    auto toCol = column + pos.second;
    if (BasicBoard::inBoard(toRow, toCol))
      jumpList.emplace_back(toRow, toCol);
  }

  return jumpList;
}

//
// is it check from a pawn
//
bool
Board::isCheckPawn(dim_t row, dim_t column) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  if (isWhite(mColor)) {
    auto toRow = row+1;
    if (toRow < BasicBoard::DIM) {
      if (column < BasicBoard::DIM-1) {
        auto code = mBoard.get(toRow, column+1);
        if (isPawn(code) and isBlack(code))
          return true;
      }
      if (column > 0) {
        auto code = mBoard.get(toRow, column-1);
        if (isPawn(code) and isBlack(code))
          return true;
      }
    }
  } else {
    auto toRow = row-1;
    if (toRow >= 0) {
      if (column < BasicBoard::DIM-1) {
        auto code = mBoard.get(toRow, column+1);
        if (isPawn(code) and isWhite(code))
          return true;
      }
      if (column > 0) {
        auto code = mBoard.get(toRow, column-1);
        if (isPawn(code) and isWhite(code))
          return true;
      }
    }
  }

  return false;
}

//
// is there check from a knight
//
bool
Board::isCheckKnight(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  auto jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto& pos : jumpList) {
    auto pcode = mBoard.get(pos.first, pos.second);
    if (isKnight(pcode) and not isSame(pcode, mColor))
      return true;
  }

  return false;
}

//
// is there a check from a bishop
//
bool
Board::isCheckBishop(dim_t row, dim_t column) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  return isCheckNW(row, column, Piece::B)
      or isCheckSW(row, column, Piece::B)
      or isCheckNE(row, column, Piece::B)
      or isCheckSE(row, column, Piece::B);
}

//
// is there a check from a rook
//
bool
Board::isCheckRook(dim_t row, dim_t column) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  return isCheckN(row, column, Piece::R)
      or isCheckW(row, column, Piece::R)
      or isCheckS(row, column, Piece::R)
      or isCheckE(row, column, Piece::R);
}

//
// is there a check from a queen
//
bool
Board::isCheckQueen(dim_t row, dim_t column) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  return isCheckN(row, column, Piece::Q)
      or isCheckNE(row, column, Piece::Q)
      or isCheckW(row, column, Piece::Q)
      or isCheckSE(row, column, Piece::Q)
      or isCheckS(row, column, Piece::Q)
      or isCheckSW(row, column, Piece::Q)
      or isCheckE(row, column, Piece::Q)
      or isCheckNW(row, column, Piece::Q);
}

//
// is there a check from the king
//
bool
Board::isCheckKing(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  auto jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto pcode = mBoard.get(pos.first, pos.second);
    if (isKing(pcode) and not isSame(pcode, mColor))
      return true;
  }

  return false;
}

//
// check if king is in danger
//
bool
Board::isCheck(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  return isCheckRook(row, column)
      or isCheckBishop(row, column)
      or isCheckKing(row, column)
      or isCheckQueen(row, column)
      or isCheckPawn(row, column)
      or isCheckKnight(row, column);
}

//
// check if there is an en passant at the given column
//
bool
Board::isEnPassant(Color color, dim_t toColumn) const noexcept
{
  if (notColor(color))
    return false;

  dim_t toRow, fromRow;
  if (isWhite(color)) {
    toRow = 4;
    fromRow = 6;
  } else {
    toRow = 3;
    fromRow = 1;
  }

  auto toCode = mBoard.get(toRow, toColumn);
  return isPawn(toCode) and not isSame(toCode, mColor)
     and isPawn(mLastMove.sPiece())
     and mLastMove.sRow() == fromRow
     and mLastMove.sColumn() == toColumn
     and mLastMove.dRow() == toRow
     and mLastMove.dColumn() == toColumn;
}

//
// Return a list of all the pawn moves.
//
std::vector<PieceMove>
Board::movePawn(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isPawn(fromCode));

  std::vector<PieceMove> moveList;
  dim_t cmpRow;
  std::function<bool(dim_t, dim_t)> cmpFunc;
  std::function<dim_t(dim_t, dim_t)> rowOp;

  // set handles to deal with black or white pawn move
  if (isWhite(mColor)) {
    cmpRow = 6;
    cmpFunc = std::less<dim_t>();
    rowOp = std::plus<dim_t>();
  } else {
    cmpRow = 1;
    cmpFunc = std::greater<dim_t>();
    rowOp = std::minus<dim_t>();
  }

  // all normal moves (i.e., pawn moves one square up or down)
  if (cmpFunc(row, cmpRow)) {
    auto toRow = rowOp(row, 1);
    // check one square straight up or down
    auto toCode = mBoard.get(toRow, column);
    if (notPiece(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    // check one square up or down, and to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = mBoard.get(toRow, toCol);
      if (not notPiece(toCode) and not isSame(toCode, mColor)) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().xPiece(toRow, toCol, toCode);
      }
    }
    // check one square up or down, and to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = mBoard.get(toRow, toCol);
      if (not notPiece(toCode) and not isSame(toCode, mColor)) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().xPiece(toRow, toCol, toCode);
      }
    }
  }

  // set comparison row for first pawn move
  cmpRow = isWhite(mColor) ? 1 : 6;

  // two moves on first move
  if (row == cmpRow) {
    if (notPiece(mBoard.get(rowOp(row, 1), column))) {
      auto toRow = rowOp(row, 2);
      if (notPiece(mBoard.get(toRow, column)))
        moveList.emplace_back(row, column, fromCode, toRow, column);
    }
  }

  // set comparison row for en passant
  cmpRow = isWhite(mColor) ? 4 : 3;

  // en passant
  if (row == cmpRow) {
    // checking column to the left
    if (column > 0) {
      auto toCol = column-1;
      if (isEnPassant(mColor, toCol)) {
        moveList.emplace_back(row, column, fromCode, rowOp(row, 1), toCol);
        moveList.back().xPiece(row, toCol, mBoard.get(row, toCol));
      }
    }
    // checking column to the right
    if (column < 7) {
      auto toCol = column+1;
      if (isEnPassant(mColor, toCol)) {
        moveList.emplace_back(row, column, fromCode, rowOp(row, 1), toCol);
        moveList.back().xPiece(row, toCol, mBoard.get(row, toCol));
      }
    }
  }

  // set comparison row for promotion
  cmpRow = isWhite(mColor) ? 6 : 1;

  // pawn promotion
  if (row == cmpRow) {
    Piece pcArr[] = {
      Piece::N, Piece::B, Piece::R, Piece::Q
    };
    auto toRow = rowOp(row, 1);
    // check one square up
    auto toCode = mBoard.get(toRow, column);
    if (notPiece(toCode)) {
      for (auto& pc : pcArr) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().dPiece(toRow, column, pc, mColor);
      }
    }
    // check diagonal square to the left
    if (column > 0) {
      auto toCol = column-1;
      toCode = mBoard.get(toRow, toCol);
      if (not notPiece(toCode) and not isSame(toCode, mColor)) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().xPiece(toRow, toCol, toCode);
          moveList.back().dPiece(toRow, toCol, pc, mColor);
        }
      }
    }
    // check diagonal square to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = mBoard.get(toRow, toCol);
      if (not notPiece(toCode) and not isSame(toCode, mColor)) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().xPiece(toRow, toCol, toCode);
          moveList.back().dPiece(toRow, toCol, pc, mColor);
        }
      }
    }
  }

  return moveList;
}

//
// move knight
//
std::vector<PieceMove>
Board::moveKnight(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isKnight(fromCode));
  std::vector<PieceMove> moveList;

  auto jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto &pos : jumpList) {
    auto toCode = mBoard.get(pos.first, pos.second);
    if (notPiece(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (not isSame(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
      moveList.back().xPiece(pos.first, pos.second, toCode);
    }
  }

  return moveList;
}

//
// move bishop
//
std::vector<PieceMove>
Board::moveBishop(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isBishop(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BasicBoard::DIM and toRow < BasicBoard::DIM; ++toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BasicBoard::DIM and toRow >= 0; ++toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 and toRow < BasicBoard::DIM; --toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and down
  for (auto toCol = column-1, toRow = row-1;
       toCol >= 0 and toRow >= 0; --toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

//
// move rook
//
std::vector<PieceMove>
Board::moveRook(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isRook(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BasicBoard::DIM; ++toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().xPiece(row, toCol, toCode);
      break;
    }
  }

  // check all moves left
  for (auto toCol = column-1; toCol >= 0; --toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().xPiece(row, toCol, toCode);
      break;
    }
  }

  // check all moves up
  for (auto toRow = row+1; toRow < BasicBoard::DIM; ++toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().xPiece(toRow, column, toCode);
      break;
    }
  }

  // check all moves down
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().xPiece(toRow, column, toCode);
      break;
    }
  }

  return moveList;
}

//
// move queen
//
std::vector<PieceMove>
Board::moveQueen(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isQueen(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right
  for (auto toCol = column+1; toCol < BasicBoard::DIM; ++toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().xPiece(row, toCol, toCode);
      break;
    }
  }

  // check all moves left
  for (auto toCol = column-1; toCol >= 0; --toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, row, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, row, toCol);
      moveList.back().xPiece(row, toCol, toCode);
      break;
    }
  }

  // check all moves up
  for (auto toRow = row+1; toRow < BasicBoard::DIM; ++toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().xPiece(toRow, column, toCode);
      break;
    }
  }

  // check all moves down
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, column);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, column);
      moveList.back().xPiece(toRow, column, toCode);
      break;
    }
  }

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BasicBoard::DIM and toRow < BasicBoard::DIM; ++toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BasicBoard::DIM and toRow >= 0; ++toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 and toRow < BasicBoard::DIM; --toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and down
  for (auto toCol = column-1, toRow = row-1;
       toCol >= 0 and toRow >= 0; --toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  return moveList;
}

//
// move king
//
std::vector<PieceMove>
Board::moveKing(dim_t row, dim_t column) const
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isKing(fromCode));
  std::vector<PieceMove> moveList;

  // normal moves
  auto jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto toCode = mBoard.get(pos.first, pos.second);
    if (notPiece(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (not isSame(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
      moveList.back().xPiece(pos.first, pos.second, toCode);
    }
  }

  // short castling
  if (canCastle()) {
    auto cRow = isWhite(mColor) ? 0 : 7;
    moveList.emplace_back(cRow, 4, mColor | Piece::K, cRow, 6);
    moveList.back().xPiece(cRow, 7, Piece::R, mColor);
  }

  // long castling
  if (canCastleLong()) {
    auto cRow = isWhite(mColor) ? 0 : 7;
    moveList.emplace_back(cRow, 4, mColor | Piece::K, cRow, 2);
    moveList.back().xPiece(cRow, 0, Piece::R, mColor);
  }

  return moveList;
}

//
// return a hash code of the board using One-at-a-Time hash
//
size_t
Board::hashCode() const noexcept
{
  size_t h = 0;

  // hash the contents of board
  for (auto &piece : mBoard) {
    h += static_cast<size_t>(piece);
    h += h << 10;
    h ^= h >> 6;
  }

  // hash the turn to move of white or black
  h += static_cast<size_t>(mColor);
  h += h << 10;
  h ^= h >> 6;

  h += h << 3;
  h += h >> 11;
  h += h << 15;

  return h;
}

//
// make a move on this board
//
Board&
Board::moveRef(const PieceMove &pMove) noexcept
{
  assert(not notColor(mColor));
  auto toRow = pMove.dRow();
  auto toCol = pMove.dColumn();

  // clear piece from where it is moving
  mBoard.clear(pMove.sRow(), pMove.sColumn());

  // clear captured piece
  if (pMove.isCapture()) {
    mBoard.clear(pMove.xRow(), pMove.xColumn());
    // check if it is mate
    if (isKing(pMove.xPiece())) {
      if (isWhite(pMove.xColor()))
        mInfo.wkMateOn();
      else
        mInfo.bkMateOn();
    }
  }

  auto piece = pMove.sPiece();
  if (isPawn(piece)) {
    auto piece = pMove.isPromo() ? pMove.dPiece() : Piece::P;
    mBoard.put(toRow, toCol, piece, mColor);
  } else if (isKing(piece)) {
    if (pMove.isCastle() or pMove.isCastleLong()) {
      if (isWhite(mColor)) {
        mInfo.rookH1On();
        mInfo.wkMovedOn();
      } else {
        mInfo.rookH8On();
        mInfo.bkMovedOn();
      }
      // clear the rook from corner square
      mBoard.clear(pMove.xRow(), pMove.xColumn());
      mBoard.put(toRow, toCol, Piece::K, mColor);
      dim_t rookCol = pMove.isCastle() ? 5 : 3;
      mBoard.put(toRow, rookCol, Piece::R, mColor);
    } else
      mBoard.put(toRow, toCol, Piece::K, mColor);
  } else {
    mBoard.put(toRow, toCol, piece, mColor);
    // set flag if a rook has moved
    if (isRook(piece)) {
      auto row = pMove.sRow();
      auto col = pMove.sColumn();
      if (isWhite(mColor)) {
        if (not mInfo.rookH1() and row == 0 and col == 7)
          mInfo.rookH1On();
        else if (not mInfo.rookA1() and row == 0 and col == 0)
          mInfo.rookA1On();
      } else {
        if (not mInfo.rookH8() and row == 7 and col == 7)
          mInfo.rookH8On();
        else if (not mInfo.rookH1() and row == 7 and col == 0)
          mInfo.rookH1On();
      }
    }
  }

  // if there was a check, but not any more, remove it
  if (isWhite(mColor) ) {
    if (mInfo.wkCheck() and not isCheck(toRow, toCol))
      mInfo.wkCheckSet(false);
  } else {
    if (mInfo.bkCheck() and not isCheck(toRow, toCol))
      mInfo.bkCheckSet(false);
  }

  // update the last move
  mLastMove = pMove;

  // flip the color
  mColor = ~mColor;

  return *this;
}

//
// is there a check in the diagonal from above and to the right
//
bool
Board::isCheckNE(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  for (auto toRow = row+1, toCol = column+1;
       toRow < BasicBoard::DIM and toCol < BasicBoard::DIM; ++toRow, ++toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is there a check in the diagonal from below and to the right
//
bool
Board::isCheckSE(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  for (auto toRow = row-1, toCol = column+1;
       toRow >= 0 and toCol < BasicBoard::DIM; --toRow, ++toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is there a check in the diagonal from below and to the left
//
bool
Board::isCheckSW(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  for (auto toRow = row-1, toCol = column-1;
       toRow >= 0 and toCol >= 0; --toRow, --toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is there a check in the diagonal from above and to the left
//
bool
Board::isCheckNW(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  for (auto toRow = row+1, toCol = column-1;
       toRow < BasicBoard::DIM and toCol >= 0; ++toRow, --toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is it check in column from above
//
bool
Board::isCheckN(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  // check against piece in colomn from above
  for (auto toRow = row+1; toRow < BasicBoard::DIM; ++toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is it check in row from right
//
bool
Board::isCheckE(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  // check against piece in same row from the right
  for (auto toCol = column+1; toCol < BasicBoard::DIM; ++toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is it check in column from below
//
bool
Board::isCheckS(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  // check against piece in column from below
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// is it check in row from left
//
bool
Board::isCheckW(dim_t row, dim_t column, Piece piece) const noexcept
{
  assert(not notColor(mColor));
  assert(BasicBoard::inBoard(row, column));

  // check against piece in the same row from left
  for (auto toCol = column-1; toCol >= 0; --toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) or not isSame(toCode, piece))
      break;
    else
      return true;
  }

  return false;
}

//
// output string representation of the board
//
std::ostream&
operator<<(std::ostream &os, const Board &board)
{
  // begin the board
  os << "{";

  auto dim = BasicBoard::DIM - 1;
  // everything but the last row
  for (dim_t row = 0; row < dim; ++row) {
    // begin the row
    os << "{";
    // everything but last square in row
    for (dim_t col = 0; col < dim; ++col)
      os << shortString(board(row, col).code()) << ", ";
    // last square in row
    os << shortString(board(row, dim).code()) << "}, ";
  }

  // everything but last square in last row
  os << "{";
  for (dim_t col = 0; col < dim; ++col)
      os << shortString(board(dim, col).code()) << ", ";
  // handle last square in last row
  os << shortString(board(dim, dim).code()) << "}";

  // close the board
  os << "}";

  return os;
}

} // namespace zoor
