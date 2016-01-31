/**
 * @file board.cc
 * @author Omar A Serrano
 * @date 2015-12-26
 */

// STL headers
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemoves.hh"
#include "board.hh"

namespace zoor {

/**
 * TODO: determine how to initialize default board.
 */
Board::Board() {}

/**
 * TODO: implement getMoves function
 */
vector<PieceMoves> Board::getMoves() const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveCopy
 */
Board Board::moveCopy(const Square &square1, const Square &square2) const noexcept
{
  return Board();
}

/**
 * TODO: implement moveRef
 */
Board& Board::moveRef(const Square &square1, const Square &square2) noexcept
{
  return *this;
}

bool Board::isEnPassant(PieceColor color, dim_type toColumn) const noexcept
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
         && getPieceColor(toCode) != mColorMove
         && mLastMove.piece() == PieceCode::PAWN
         && mLastMove.fromRow() == fromRow
         && mLastMove.fromColumn() == toColumn
         && mLastMove.toRow() == toRow
         && mLastMove.toColumn() = toColumn;
}

/**
 * TODO: implement moveWhitePawn
 */
vector<PieceMove> Board::movePawn(dim_type row, dim_type column) const noexcept
{
  vector<PieceMove> moveList;
  auto fromCode = mColorMove & PieceCode::PAWN;

  dim_type cmpRow;
  std::function<bool(dim_type, dim_type)> cmpFunc;
  std::function<dim_type(dim_type, dim_type)> rowOp;

  // set handles to deal with black or white pawn move
  if (mColorMove == PieceColor::WHITE) {
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
    auto mrow = rowOp(row, 1);
    // check one square straight up or down
    auto toCode = get(mrow, column);
    if (getPieceCode(toCode) == PieceCode::NONE) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setDestination(mrow, column);
    }
    // check one square up or down, and to the left
    if (column > 0) {
      auto mcol = column-1;
      toCode = get(mrow, mcol);
      if (getPieceColor(toCode) != PieceColor::WHITE) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setCapture(mrow, mcol, toCode);
        moveList.back().setDestination(mrow, mcol);
      }
    }
    // check one square up or down, and to the right
    if (column < 7) {
      auto mcol = column+1;
      toCode = get(mrow, mcol);
      if (getPieceColor(toCode) != PieceColor::WHITE) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setCapture(mrow, mcol, toCode);
        moveList.back().setDestination(mrow, mcol);
      }
    }
  }

  // set comparison row for first pawn move
  cmpRow = PieceColor::WHITE ? 1 : 6;

  // two moves on first move
  if (row == cmpRow) {
    auto mrow = rowOp(row, 2);
    auto toCode = get(mrow, column);
    if (getPieceCode(toCode) == PieceCode::NONE) {
      moveList.emplace_back(row, column, fromCode);
      moveList.back().setDestination(mrow, column);
    }
  }

  // set comparison row for en passant
  cmpRow = PieceColor::WHITE ? 5 : 4;

  // en passant
  if (row == cmpRow) {
    // checking column to the left
    if (column > 0) {
      auto mcol = column-1;
      if (isEnPassant(mColorMove, mcol)) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setCapture(row, mcol, get(row, mcol));
        moveList.back().setDestination(rowOp(row, 1), mcol);
      }
    }
    // checking column to the right
    if (column < 7) {
      auto mcol = column+1;
      if (isEnPassant(mColorMove, mcol)) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setCapture(row, mcol, get(row, mcol));
        moveList.back().setDestination(rowOp(row, 1), mcol);
      }
    }
  }

  // set comparison row for promotion
  cmpRow = PieceColor::WHITE ? 6 : 1;

  // pawn promotion
  if (row == cmpRow) {
    PieceCode pcArr[] = {
      PieceCode::KNIGHT, PieceCode::BISHOP,
      PieceCode::ROOK, PieceCode::QUEEN
    };
    auto mrow = rowOp(row, 1);
    // check one square up
    auto toCode = get(mrow, column);
    if (getPieceCode(toCode) == PieceCode::NONE) {
      for (auto& pc : pcArr) {
        moveList.emplace_back(row, column, fromCode);
        moveList.back().setPromotion(mrow, column, pc, mColorMove);
      }
    }
    // check diagonal square to the left
    if (column > 0) {
      auto mcol = column-1;
      toCode = get(mrow, mcol);
      if (getPieceCode(toCode) != PieceCode::NONE
          && getPieceColor(toCode) != mColorMove) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(mrow, mcol, toCode);
          moveList.back().setPromotion(mrow, mcol, pc, mColorMove);
        }
      }
    }
    // check diagonal square to the right
    if (column < 7) {
      auto mcol = column+1;
      toCode = get(mrow, mcol);
      if (getPieceCode(toCode) != PieceCode::NONE
          && getPieceColor(toCode) != mColorMove) {
        for (auto& pc : pcArr) {
          moveList.emplace_back(row, column, fromCode);
          moveList.back().setCapture(mrow, mcol, toCode);
          moveList.back().setPromotion(mrow, mcol, pc, mColorMove);
        }
      }
    }
  }

  return moveList;
}

/**
 * TODO: implement moveBlackPawn
 */
PieceMoves Board::moveBlackPawn(dim_type row, dim_type column) const noexcept
{
  return PieceMoves;
}

/**
 * TODO: implement moveKnight
 */
vector<PieceMoves> Board::moveKnight(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveBishop
 */
vector<PieceMoves> Board::moveBishop(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveRook
 */
vector<PieceMoves> Board::moveRook(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveQueen
 */
vector<PieceMoves> Board::moveQueen(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveKing
 */
vector<PieceMoves> Board::moveKing(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement getBoardsFromMoves function
 */
vector<Board> Board::getBoardsFromMoves() const noexcept
{
  return vector<Board>();
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
Board& Board::makeMove(const Square &square1, const Square &square2) noexcept
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

PieceCount Board::whiteCount() const noexcept
{
  return mWhiteCount;
}

PieceCount Board::blackCount() const noexcept
{
  return mBlackCount;
}

pair<Square, Square> Board::lastMove() const noexcept
{
  return mLastMove;
}

Square Board::operator()(dim_type row, dim_type column) const noexcept
{
  assert(row < BOARD_DIM && column < BOARD_DIM);
  auto code = get(row, column);
  return Square(row, column, getPieceCode(code), getPieceColor(code));
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
  return board1.mColorMove == board2.mColorMove
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

BoardIterator& BoardIterator::operator+=(BoardIterator::difference_type value)
{
  mIndex += value;
  if (mIndex < static_cast<difference_type>(0)
      || mIndex > static_cast<difference_type>(LAST_INDEX))
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  return *this;
}

BoardIterator& BoardIterator::operator-=(BoardIterator::difference_type value)
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

bool operator==(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
{
  return bi1.mBoardPtr == bi2.mBoardPtr && bi1.mIndex == bi2.mIndex;
}

bool operator!=(const BoardIterator &bi1, const BoardIterator &bi2) noexcept
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
