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

using PieceCount::count_type;

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
