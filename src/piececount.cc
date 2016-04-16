/**
 * @file piececount.cc
 * @author Omar A Serrano
 * @date 2015-12-21
 */

#include <cstdlib>
#include <cassert>
#include <iostream>

#include "piececode.hh"
#include "piececount.hh"

namespace zoor {

using count_type = PieceCount::count_type;

////////////////////////////////////////////////////////////////////////////////
// clear all the pieces
////////////////////////////////////////////////////////////////////////////////
PieceCount& PieceCount::clear() noexcept
{
  mKings = 0;
  mQueens = 0;
  mRooks = 0;
  mBishops = 0;
  mKnights = 0;
  mPawns = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// decrease the count of a piece
////////////////////////////////////////////////////////////////////////////////
PieceCount& PieceCount::operator-=(PieceCode piece) noexcept
{
  switch (piece) {
  case PieceCode::PAWN:
    --mPawns;
    break;
  case PieceCode::KNIGHT:
    --mKnights;
    break;
  case PieceCode::BISHOP:
    --mBishops;
    break;
  case PieceCode::ROOK:
    --mRooks;
    break;
  case PieceCode::QUEEN:
    --mQueens;
    break;
  case PieceCode::KING:
    --mKings;
    break;
  default:
    break;
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// increase the count for piece by one
////////////////////////////////////////////////////////////////////////////////
count_type PieceCount::plus(PieceCode piece) noexcept
{
  return plus(piece, static_cast<count_type>(1));
}

////////////////////////////////////////////////////////////////////////////////
// increase the count for piece by a given value
////////////////////////////////////////////////////////////////////////////////
count_type PieceCount::plus(PieceCode piece, count_type value) noexcept
{
  switch (piece) {
  case PieceCode::PAWN:
    mPawns += value;
    return mPawns;
  case PieceCode::KNIGHT:
    mKnights += value;
    return mKnights;
  case PieceCode::BISHOP:
    mBishops += value;
    return mBishops;
  case PieceCode::ROOK:
    mRooks += value;
    return mRooks;
  case PieceCode::QUEEN:
    mQueens += value;
    return mQueens;
  case PieceCode::KING:
    mKings += value;
    return mKings;
  default:
    std::cerr << "Bad PieceCode value for plus." << std::endl;
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
// decrease the count for piece by one
////////////////////////////////////////////////////////////////////////////////
count_type PieceCount::minus(PieceCode piece) noexcept
{
  return minus(piece, static_cast<count_type>(1));
}

////////////////////////////////////////////////////////////////////////////////
// decrease the count for piece by a given value
////////////////////////////////////////////////////////////////////////////////
count_type PieceCount::minus(PieceCode piece, count_type value) noexcept
{
  switch (piece) {
  case PieceCode::PAWN:
    assert(mPawns >= value);
    mPawns -= value;
    return mPawns;
  case PieceCode::KNIGHT:
    assert(mKnights >= value);
    mKnights -= value;
    return mKnights;
  case PieceCode::BISHOP:
    assert(mBishops >= value);
    mBishops -= value;
    return mBishops;
  case PieceCode::ROOK:
    assert(mRooks >= value);
    mRooks -= value;
    return mRooks;
  case PieceCode::QUEEN:
    assert(mQueens >= value);
    mQueens -= value;
    return mQueens;
  case PieceCode::KING:
    assert(mKings >= value);
    mKings -= value;
    return mKings;
  default:
    std::cerr << "Bad PieceCode value for minus." << std::endl;
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
// set the count for a piece
////////////////////////////////////////////////////////////////////////////////
PieceCount& PieceCount::setCount(PieceCode piece, count_type value) noexcept
{
  switch (piece) {
  case PieceCode::PAWN:
    mPawns = value;
    break;
  case PieceCode::KNIGHT:
    mKnights = value;
    break;
  case PieceCode::BISHOP:
    mBishops = value;
    break;
  case PieceCode::ROOK:
    mRooks = value;
    break;
  case PieceCode::QUEEN:
    mQueens = value;
    break;
  case PieceCode::KING:
    mKings = value;
    break;
  default:
    std::cerr << "Bad PieceCode value for minus." << std::endl;
    exit(EXIT_FAILURE);
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// output operator for piece count
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &os, const PieceCount &pc)
{
  os << "{kings=" << pc.mKings
     << ", queens=" << pc.mQueens
     << ", rooks=" << pc.mRooks
     << ", bishops=" << pc.mBishops
     << ", knights=" << pc.mKnights
     << ", pawns=" << pc.mPawns
     << "}";
  return os;
}

////////////////////////////////////////////////////////////////////////////////
// equality operator for piece count
////////////////////////////////////////////////////////////////////////////////
bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept
{
  return pc1.mKings == pc2.mKings
      && pc1.mQueens == pc2.mQueens
      && pc1.mRooks == pc2.mRooks
      && pc1.mBishops == pc2.mBishops
      && pc1.mKnights == pc2.mKnights
      && pc1.mPawns == pc2.mPawns;
}

////////////////////////////////////////////////////////////////////////////////
// non-equality operator for piece count
////////////////////////////////////////////////////////////////////////////////
bool operator!=(const PieceCount &pc1, const PieceCount &pc2) noexcept
{
  return !(pc1 == pc2);
}

} // namespace zoor
