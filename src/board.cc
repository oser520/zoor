/////////////////////////////////////////////////////////////////////////////////////
/// @file board.cc
/// @author Omar A Serrano
/// @date 2015-12-26
/////////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <bitset>
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

/////////////////////////////////////////////////////////////////////////////////////
// Board
/////////////////////////////////////////////////////////////////////////////////////

//
// default ctor
//
Board::Board()
  : mColor(Color::W) {}

//
// constructor with list of pieces
//
Board::Board
  (const std::vector<Square> &squareList,
   const Color color,
   const BoardInfo &boardInfo,
   const PieceMove &lastMove)
  : mColor(color),
    mLastMove(lastMove),
    mInfo(boardInfo)
{
  assert(!notColor(mColor));
  assert(!squareList.empty());

  for (auto& sq : squareList)
    mBoard.put(sq.row(), sq.column(), sq.code());

  if (!isLastMoveOk())
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
    if (!mInfo.wkCastle())
      return false;
    row = 0;
  } else {
    if (!mInfo.bkCastle())
      return false;
    row = 7;
  }

  // path for castling is clear
  if (!notPiece(mBoard.get(row, 5)) || !notPiece(mBoard.get(row, 6)))
    return false;

  // no checks on path to castle
  if (isCheck(row, 5) || isCheck(row, 6))
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
    if (!mInfo.wkCastleLong())
      return false;
    row = 1;
  } else {
    if (!mInfo.bkCastleLong())
      return false;
    row = 7;
  }

  // path for castling is clear
  if (!notPiece(mBoard.get(row, 3)) || !notPiece(mBoard.get(row, 2)))
    return false;

  // no checks on path to castle
  if (isCheck(row, 3) || isCheck(row, 2))
    return false;

  return true;
}

//
// get the moves that can be made from a given square
//
std::vector<PieceMove>
Board::getMoves(dim_t row, dim_t column) const
{
  assert(!notColor(mColor));
  std::vector<PieceMove> moveList;

  auto code = mBoard.get(row, column);

  if (notPiece(code) || !isSame(code, mColor))
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
    // should never get here
    assert(false);
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
  assert(!notColor(mColor));

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
  assert(isSame(pc, pMove.sPiece()) && isSame(pc, pMove.sColor()));

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
  if (!notPiece(piece)) {
    // check that there is no piece from square where piece moved from
    if (!notPiece(mBoard.get(mLastMove.sRow(), mLastMove.sColumn())))
      return false;

    if (mLastMove.isCastle()) {
      if (isWhite(mLastMove.sColor())) {
        auto pcode = mBoard.get(0, 7);
        if (!isRook(pcode) || !isWhite(pcode))
          return false;
        pcode = mBoard.get(0, 4);
        if (!isKing(pcode) || !isWhite(pcode))
          return false;
        // check if board info allows castling
        if (!mInfo.wkCastle())
          return false;
      } else {
        auto pcode = mBoard.get(7, 7);
        if (!isRook(pcode) || !isBlack(pcode))
          return false;
        pcode = mBoard.get(7, 4);
        if (!isKing(pcode) || !isBlack(pcode))
          return false;
        // check if board info allows castling
        if (!mInfo.bkCastle())
          return false;
      }
    } else if (mLastMove.isCastleLong()) {
      if (isWhite(mLastMove.sColor())) {
        auto pcode = mBoard.get(0, 0);
        if (!isRook(pcode) || !isWhite(pcode))
          return false;
        pcode = mBoard.get(0, 2);
        if (!isKing(pcode) || !isWhite(pcode))
          return false;
        // check if board info allows castling
        if (!mInfo.wkCastleLong())
          return false;
      } else {
        auto pcode = mBoard.get(7, 0);
        if (!isRook(pcode) || !isBlack(pcode))
          return false;
        pcode = mBoard.get(7, 2);
        if (!isKing(pcode) || !isBlack(pcode))
          return false;
        // check if board info allows castling
        if (!mInfo.bkCastleLong())
          return false;
      }
    } else if (mLastMove.isPromo()) {
      auto pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      auto ppromo = mLastMove.dPiece();
      if (!isSame(pcode, ppromo) || !isSame(pcode, pcolor))
        return false;
    } else if (mLastMove.isEnPassant()) {
      // check there's no piece at capture square
      auto pcode = mBoard.get(mLastMove.xRow(), mLastMove.xColumn());
      if (!notPiece(pcode))
        return false;
      pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      if (!isPawn(pcode) || !isSame(pcode, pcolor))
        return false;
    } else {
      auto pcode = mBoard.get(mLastMove.dRow(), mLastMove.dColumn());
      auto pcolor = mLastMove.sColor();
      if (!isSame(pcode, piece) || !isSame(pcode, pcolor))
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
  assert(inBoard(row, column));
  jump_list jumpList;

  for (auto& pos : positions) {
    auto toRow = row + pos.first;
    auto toCol = column + pos.second;
    if (inBoard(toRow, toCol))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  if (isWhite(mColor)) {
    auto toRow = row+1;
    if (toRow < BasicBoard::DIM) {
      if (column < BasicBoard::DIM-1) {
        auto code = mBoard.get(toRow, column+1);
        if (isPawn(code) && isBlack(code))
          return true;
      }
      if (column > 0) {
        auto code = mBoard.get(toRow, column-1);
        if (isPawn(code) && isBlack(code))
          return true;
      }
    }
  } else {
    auto toRow = row-1;
    if (toRow >= 0) {
      if (column < BasicBoard::DIM-1) {
        auto code = mBoard.get(toRow, column+1);
        if (isPawn(code) && isWhite(code))
          return true;
      }
      if (column > 0) {
        auto code = mBoard.get(toRow, column-1);
        if (isPawn(code) && isWhite(code))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  auto jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto& pos : jumpList) {
    auto pcode = mBoard.get(pos.first, pos.second);
    if (isKnight(pcode) && !isSame(pcode, mColor))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  return isCheckNW(row, column, Piece::B)
      || isCheckSW(row, column, Piece::B)
      || isCheckNE(row, column, Piece::B)
      || isCheckSE(row, column, Piece::B);
}

//
// is there a check from a rook
//
bool
Board::isCheckRook(dim_t row, dim_t column) const noexcept
{
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  return isCheckN(row, column, Piece::R)
      || isCheckW(row, column, Piece::R)
      || isCheckS(row, column, Piece::R)
      || isCheckE(row, column, Piece::R);
}

//
// is there a check from a queen
//
bool
Board::isCheckQueen(dim_t row, dim_t column) const noexcept
{
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  return isCheckN(row, column, Piece::Q)
      || isCheckNE(row, column, Piece::Q)
      || isCheckW(row, column, Piece::Q)
      || isCheckSE(row, column, Piece::Q)
      || isCheckS(row, column, Piece::Q)
      || isCheckSW(row, column, Piece::Q)
      || isCheckE(row, column, Piece::Q)
      || isCheckNW(row, column, Piece::Q);
}

//
// is there a check from the king
//
bool
Board::isCheckKing(dim_t row, dim_t column) const
{
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  auto jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto pcode = mBoard.get(pos.first, pos.second);
    if (isKing(pcode) && !isSame(pcode, mColor))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  return isCheckRook(row, column)
      || isCheckBishop(row, column)
      || isCheckKing(row, column)
      || isCheckQueen(row, column)
      || isCheckPawn(row, column)
      || isCheckKnight(row, column);
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
  return isPawn(toCode) && !isSame(toCode, mColor)
      && isPawn(mLastMove.sPiece())
      && mLastMove.sRow() == fromRow
      && mLastMove.sColumn() == toColumn
      && mLastMove.dRow() == toRow
      && mLastMove.dColumn() == toColumn;
}

//
// Return a list of all the pawn moves.
//
std::vector<PieceMove>
Board::movePawn(dim_t row, dim_t column) const
{
  assert(!notColor(mColor));
  assert(inBoard(row, column));
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
      if (!isSame(toCode, mColor)) {
        moveList.emplace_back(row, column, fromCode, toRow, toCol);
        moveList.back().xPiece(toRow, toCol, toCode);
      }
    }
    // check one square up or down, and to the right
    if (column < 7) {
      auto toCol = column+1;
      toCode = mBoard.get(toRow, toCol);
      if (!isSame(toCode, mColor)) {
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
  cmpRow = isWhite(mColor) ? 5 : 4;

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
      if (!notPiece(toCode) && !isSame(toCode, mColor)) {
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
      if (!notPiece(toCode) && !isSame(toCode, mColor)) {
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isKnight(fromCode));
  std::vector<PieceMove> moveList;

  auto jumpList = jump(row, column, JUMP_KNIGHT);
  for (auto &pos : jumpList) {
    auto toCode = mBoard.get(pos.first, pos.second);
    if (notPiece(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (!isSame(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode);
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isBishop(fromCode));
  std::vector<PieceMove> moveList;

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BasicBoard::DIM && toRow < BasicBoard::DIM; ++toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BasicBoard::DIM && toRow >= 0; ++toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 && toRow < BasicBoard::DIM; --toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().xPiece(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and down
  for (auto toCol = column-1, toRow = row-1;
       toCol >= 0 && toRow >= 0; --toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));
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
      moveList.back().setCapture(row, toCol, toCode);
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
      moveList.back().setCapture(row, toCol, toCode);
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
      moveList.back().setCapture(toRow, column, toCode);
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
      moveList.back().setCapture(toRow, column, toCode);
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));
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
      moveList.back().setCapture(row, toCol, toCode);
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
      moveList.back().setCapture(row, toCol, toCode);
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
      moveList.back().setCapture(toRow, column, toCode);
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
      moveList.back().setCapture(toRow, column, toCode);
      break;
    }
  }

  // check all moves right and up
  for (auto toCol = column+1, toRow = row+1;
       toCol < BasicBoard::DIM && toRow < BasicBoard::DIM; ++toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves right and down
  for (auto toCol = column+1, toRow = row-1;
       toCol < BasicBoard::DIM && toRow >= 0; ++toCol, --toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
      break;
    }
  }

  // check all moves left and up
  for (auto toCol = column-1, toRow = row+1;
       toCol >= 0 && toRow < BasicBoard::DIM; --toCol, ++toRow) {
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
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
    auto toCode = mBoard.get(toRow, toCol);
    if (isSame(toCode, mColor))
      break;
    else if (notColor(toCode))
      moveList.emplace_back(row, column, fromCode, toRow, toCol);
    else {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(toRow, toCol, toCode);
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));
  auto fromCode = mBoard.get(row, column);
  assert(isKing(fromCode));
  std::vector<PieceMove> moveList;

  // normal moves
  auto jumpList = jump(row, column, JUMP_KING);
  for (auto& pos : jumpList) {
    auto toCode = mBoard.get(pos.first, pos.second);
    if (notPiece(toCode))
      moveList.emplace_back(row, column, fromCode, pos.first, pos.second);
    else if (!isSame(toCode, mColor)) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setCapture(pos.first, pos.second, toCode);
    }
  }

  // short castling
  if (canCastle()) {
    moveList.emplace_back();
    moveList.back().doCastle(mColor);
  }

  // long castling
  if (canCastleLong()) {
    moveList.emplace_back();
    moveList.back().doCastleLong(mColor);
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
Board::moveRef(const PieceMove &pieceMove) noexcept
{
  assert(!notColor(mColor));
  auto toRow = pieceMove.toRow();
  auto toCol = pieceMove.toColumn();

  // clear piece from where it is moving
  mBoard.clear(pieceMove.fromRow(), pieceMove.fromColumn());

  // clear captured piece
  if (pieceMove.isCapture()) {
    mBoard.clear(pieceMove.captureRow(), pieceMove.captureColumn());
    // check if it is mate
    if (isKing(pieceMove.capturePiece())) {
      if (isWhite(pieceMove.captureColor()))
        mInfo.wkMateOn();
      else
        mInfo.bkMateOn();
    }
  }

  auto piece = pieceMove.fromPiece();
  if (isPawn(piece)) {
    auto piece = pieceMove.isPromo() ? pieceMove.promoPiece() : Piece::P;
    mBoard.put(toRow, toCol, piece);
  } else if (isKing(piece)) {
    if (!pieceMove.isCastle() && !pieceMove.isCastleLong())
      mBoard.put(toRow, toCol, Piece::K);
    else if (pieceMove.isCastle()) {
      dim_t row;
      if (isWhite(mColor)) {
        row = 0;
        mInfo.rookH1On();
        mInfo.wkMovedOn();
      } else {
        row = 7;
        mInfo.rookH8On();
        mInfo.bkMovedOn();
      }
      // clear the rook from corner square
      mBoard.clear(row, 7);
      mBoard.put(row, 6, Piece::K);
      mBoard.put(row, 5, Piece::R);
    } else {  // is long castling
      dim_t row;
      if (isWhite(mColor)) {
        row = 0;
        mInfo.rookA1On();
        mInfo.wkMovedOn();
      } else {
        row = 7;
        mInfo.rookA8On();
        mInfo.bkMovedOn();
      }
      // clear the rook from corner square
      mBoard.clear(row, 0);
      mBoard.put(row, 2, Piece::K);
      mBoard.put(row, 3, Piece::R);
    }
  } else {
    mBoard.put(toRow, toCol, piece);
    // set flag if a rook has moved
    if (isRook(piece)) {
      auto row = pieceMove.fromRow();
      auto col = pieceMove.fromColumn();
      if (isWhite(mColor)) {
        if (!mInfo.rookH1() && row == 0 && col == 7)
          mInfo.rookH1On();
        else if (!mInfo.rookA1() && row == 0 && col == 0)
          mInfo.rookA1On();
      } else {
        if (!mInfo.rookH8() && row == 7 && col == 7)
          mInfo.rookH8On();
        else if (!mInfo.rookH1() && row == 7 && col == 0)
          mInfo.rookH1On();
      }
    }
  }

  // if there was a check, but not any more, remove it
  if (isWhite(mColor) ) {
    if (mInfo.wkCheck() && !isCheck(toRow, toCol))
      mInfo.wkCheckSet(false);
  } else {
    if (mInfo.bkCheck() && !isCheck(toRow, toCol))
      mInfo.bkCheckSet(false);
  }

  // update the last move
  mLastMove = pieceMove;

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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  for (auto toRow = row+1, toCol = column+1;
       toRow < BasicBoard::DIM && toCol < BasicBoard::DIM; ++toRow, ++toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  for (auto toRow = row-1, toCol = column+1;
       toRow >= 0 && toCol < BasicBoard::DIM; --toRow, ++toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  for (auto toRow = row-1, toCol = column-1;
       toRow >= 0 && toCol >= 0; --toRow, --toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  for (auto toRow = row+1, toCol = column-1;
       toRow < BasicBoard::DIM && toCol >= 0; ++toRow, --toCol) {
    auto toCode = mBoard.get(toRow, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  // check against piece in colomn from above
  for (auto toRow = row+1; toRow < BasicBoard::DIM; ++toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  // check against piece in row from the right
  for (auto toCol = row+1; toCol < BasicBoard::DIM; ++toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  // check against piece in column from below
  for (auto toRow = row-1; toRow >= 0; --toRow) {
    auto toCode = mBoard.get(toRow, column);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  assert(!notColor(mColor));
  assert(inBoard(row, column));

  // check against piece in row from left
  for (auto toCol = row-1; toCol >= 0; --toCol) {
    auto toCode = mBoard.get(row, toCol);
    if (notColor(toCode))
      continue;
    else if (isSame(toCode, mColor) || !isSame(toCode, piece))
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
  for (size_t row = 0; row < dim; ++row) {
    // begin the row
    os << "{";
    // everything but last square in row
    for (size_t col = 0; col < dim; ++col)
      os << shortStringCode(board.get(row, col)) << ", ";
    // last square in row
    os << shortStringCode(board.get(row, dim)) << "}, ";
  }

  // everything but last square in last row
  os << "{";
  for (size_t col = 0; col < dim; ++col)
      os << shortStringCode(board.get(dim, col)) << ", ";
  // handle last square in last row
  os << shortStringCode(board.get(dim, dim)) << "}";

  // close the board
  os << "}";

  return os;
}

} // namespace zoor
