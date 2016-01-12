/**
 * @file piececount.cc
 * @author Omar A Serrano
 * @date 2015-12-21
 */

#include <iostream>

#include "piececount.hh"

namespace zoor {

PieceCount::PieceCount() noexcept
  : mKings(1),
    mQueens(1),
    mRooks(2),
    mBishops(2),
    mKnights(2),
    mPawns(8),
    mTotal(16) {}

PieceCount& PieceCount::init() noexcept
{
  mKings = 1;
  mQueens = 1;
  mRooks = 2;
  mBishops = 2;
  mKnights = 2;
  mPawns = 8;
  mTotal = 16;
  return *this;
}

PieceCount& PieceCount::clear() noexcept
{
  mKings = 0;
  mQueens = 0;
  mRooks = 0;
  mBishops = 0;
  mKnights = 0;
  mPawns = 0;
  mTotal = 0;
  return *this;
}

count_type PieceCount::plus(PieceCode piece) noexcept
{
  return plus(piece, 1);
}

count_type PieceCount::plus(PieceCode piece, count_type value) noexcept
{
  switch (piece) {
  case PieceCode::PAWN:
    mPawns += value;
    return mPawns;
  case PieceCode::KNIGHT:
    mKnights += value;
    return mPawns;
  case PieceCode::BISHOP:
    mBishops += value;
    return mPawns;
  case PieceCode::ROOK:
    mRooks += value;
    return mPawns;
  case PieceCode::QUEEN:
    mQueens += value;
    return mPawns;
  case PieceCode::KING:
    mKings += value;
    return mPawns;
  default:
    std::cerr << "Bad PieceCode value for plus." << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::ostream& operator<<(std::ostream &os, const PieceCount &pc)
{
  os << "{kings=" << pc.mKings
     << ", queens=" << pc.mQueens
     << ", rooks=" << pc.mRooks
     << ", bishops=" << pc.mBishops
     << ", knights=" << pc.mKnights
     << ", pawns=" << pc.mPawns
     << ", total=" << pc.mTotal
     << "}";
  return os;
}

bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept
{
  return pc1.mKings == pc2.mKings
      && pc1.mQueens == pc2.mQueens
      && pc1.mRooks == pc2.mRooks
      && pc1.mBishops == pc2.mBishops
      && pc1.mKnights == pc2.mKnights
      && pc1.mPawns == pc2.mPawns;
}

bool operator!=(const PieceCount &pc1, const PieceCount &pc2) noexcept
{
  return !(pc1 == pc2);
}

} // namespace zoor
