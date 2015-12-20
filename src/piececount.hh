/**
 * @file piececount.hh
 * @author Omar A Serrano
 * @date 2015-19-18
 */

#ifndef _PIECECOUNT_H
#define _PIECECOUNT_H

#include <iostream>

namespace zoor {

/**
 * PieceCount maintains a count of the number of pieces on the board.
 */
struct PieceCount {
  using count_type = unsigned short;

  count_type mKings;
  count_type mQueens;
  count_type mRooks;
  count_type mBishops;
  count_type mKnights;
  count_type mPawns;
  count_type mTotal;

  enum class Pos { START };

  /**
   * Construct a PieceCount with the normal number of pieces at the beginning of
   * a game, with:
   *
   * @li 1 king
   * @li 1 queen
   * @li 2 rooks
   * @li 2 bishops
   * @li 2 knights
   * @li 8 pawns
   */
  PieceCount() noexcept;
  PieceCount(const PieceCount &pcount) noexcept = default;
  PieceCount& operator=(const PieceCount &pcount) noexcept = default;
  ~PieceCount() noexcept = default;

  /**
   * Sets the piece count to what it would be at the beginning of the game.
   * The default constructor initializes a PieceCount to the same state,
   * so we would use this after a board has already been in use and we want
   * to re-set the state.
   *
   * @return A reference to this PieceCount.
   */
  PieceCount& init() noexcept;
};

PieceCount::PieceCount() noexcept
  : mKings(1),
    mQueens(1),
    mRooks(2),
    mBishops(2),
    mKnights(2),
    mPawns(8),
    mTotal(16) {}

inline PieceCount& PieceCount::init() noexcept
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

/**
 * Format a PieceCount for an output stream.
 *
 * @param os The output stream.
 * @param pc A PieceCount object.
 * @return A reference to the output stream.
 */
inline std::ostream& operator<<(std::ostream &os, const PieceCount &pc)
{
  return os << "{kings=" << mKings
            << ", queens=" << mQueens
            << ", rooks=" << mRooks
            << ", bishops=" << mBishops
            << ", knights=" << mKnights
            << ", pawns=" << mPawns
            << ", total=" << mTotal
            << "}";
  return os;
}

} // namespace zoor

#endif 
