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

/**
 * TODO: implement movePawn
 */
PieceMoves Board::movePawn(dim_type row, dim_type column) const noexcept
{
  return (mColorMove == PieceColor::WHITE) ?
          moveWhitePawn(row, column) : moveBlackPawn(row, column);
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
