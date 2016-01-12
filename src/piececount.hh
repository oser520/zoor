/**
 * @file piececount.hh
 * @author Omar A Serrano
 * @date 2015-12-19
 */

#ifndef _PIECECOUNT_H
#define _PIECECOUNT_H

#include <iostream>
#include <stdexcept>

#include "piececode.hh"

namespace zoor {

/**
 * PieceCount maintains a count of the number of pieces on the board.
 */
class PieceCount {
  friend bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept;
  friend std::ostream& operator<<(std::ostream &os, const PieceCount &pc);

public:
  /**
   * Alias for the integral type for the count of each piece.
   */
  using count_type = unsigned short;

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

  /**
   * @brief Copy constructor.
   * @param pcount The @c PieceCount to be copied.
   * @throw Never throws.
   */
  PieceCount(const PieceCount &pcount) noexcept = default;

  /**
   * @brief Move constructor.
   * @param pcount The @c PieceCount to be moved.
   * @throw Never throws.
   */
  PieceCount(PieceCount &&pcount) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param pcount The @c PieceCount to be copied.
   * @return A reference to this @c PieceCount.
   * @throw Never throws.
   */
  PieceCount& operator=(const PieceCount &pcount) noexcept = default;

  /**
   * @brief Move assignment operator.
   * @param pcount The @c PieceCount to be moved.
   * @return A reference to this @c PieceCount.
   * @throw Never throws.
   */
  PieceCount& operator=(PieceCount &&pcount) noexcept = default;

  /**
   * @brief Default destructor.
   * @throw Never throws.
   */
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

  /**
   * @brief Sets the count of every piece to zero.
   * @return A reference to this PieceCount.
   * @throw Never throws.
   */
  PieceCount& clear() noexcept;

  /**
   * @brief Increments the count for a given piece by one.
   * @param piece The @c PieceCode of the piece to be incremented.
   * @return The new count for the piece.
   * @throw Never throws.
   */
  count_type plus(PieceCode piece) noexcept;

  /**
   * @brief Increments the count for a given piece by a given number.
   * @param pc The @c PieceCode of the piece to be incremented.
   * @param value The value to be incremented by.
   * @return The new count for the piece.
   * @throw Never throws.
   */
  count_type plus(PieceCode piece, count_type value) noexcept;

  /**
   * @brief Decreases the count for a given piece by one.
   * @detail Won't decrease the count of a given piece below zero.
   * @param piece The @c PieceCode with count being decreased.
   * @return The new count for the piece.
   * @throw Never throws.
   */
  count_type minus(PieceCode piece) noexcept;

  /**
   * @brief Decreases the count for a given piece by a given value.
   * @detail Won't decrease the count of a given piece below zero.
   * @param piece The @c PieceCode with count being decreased.
   * @param value The value by which the count of the piece is being decreased.
   * @return The new count for the piece.
   * @throw Never throws.
   */
  count_type minus(PieceCode piece, count_type value) noexcept;

  /**
   * @brief Sets the count for a given piece.
   * @detail Won't set value below zero.
   * @param piece The @c PieceCode for the piece's count being set.
   * @param value The value of the count for the piece.
   * @return A reference to this @c PieceCount.
   * @throw Never throws.
   */
  PieceCount& setCount(PieceCode piece, count_type value) noexcept;

  /**
   * @brief Get the piece count for kings.
   * @return A copy of the count for kings.
   * @throw Never throws.
   */
  count_type kings() const noexcept { return mKings; }

  /**
   * @brief Get the piece count for queens.
   * @return A copy of the count for queens.
   * @throw Never throws.
   */
  count_type queens() const noexcept { return mQueens; }

  /**
   * @brief Get the piece count for rooks.
   * @return A copy of the count for rooks.
   * @throw Never throws.
   */
  count_type rooks() const noexcept { return mRooks; }

  /**
   * @brief Get the piece count for bishops.
   * @return A copy of the count for bishops.
   * @throw Never throws.
   */
  count_type bishops() const noexcept { return mBishops; }

  /**
   * @brief Get the piece count for knights.
   * @return A copy of the count for knights.
   * @throw Never throws.
   */
  count_type knights() const noexcept { return mKnights; }

  /**
   * @brief Get the piece count for pawns.
   * @return A copy of the count for pawns.
   * @throw Never throws.
   */
  count_type pawns() const noexcept { return mPawns; }

  /**
   * @brief Get the total piece count.
   * @return A copy of the total piece count.
   * @throw Never throws.
   */
  count_type total() const noexcept { return mTotal; }

  /**
   * Obtain the value of the pawns on the board.
   *
   * The value of the pawns on the board is simply the number of pawns times the
   * value of each pawn. The object is not modified and no exceptions are thrown.
   *
   * @return The value of the pawns on the board.
   */
  size_t valuePawns() const noexcept;

  /**
   * Obtain the value of the knights on the board.
   *
   * The value of the knights on the board is simply the number of knights times the
   * value of each knight. The object is not modified and no exceptions are thrown.
   *
   * @return The value of the knights on the board.
   */
  size_t valueKnights() const noexcept;

  /**
   * Obtain the value of the bishops in the board.
   *
   * The value of the bishops on the board is simply the number of bishops times the
   * value of each bishop. The object is not modified and no exceptions are thrown.
   *
   * @return The value of the bishops on the board.
   */
  size_t valueBishops() const noexcept;

  /**
   * Obtain the value of the rooks in the board.
   *
   * The value of the rooks on the board is simply the number of rooks times the
   * value of each rook. The object is not modified and no exceptions are thrown.
   *
   * @return The value of the rooks on the board.
   */
  size_t valueRooks() const noexcept;

  /**
   * Obtain the value of the queens in the board.
   *
   * The value of the queens on the board is simply the number of queens times the
   * value of each queen. The object is not modified and no exceptions are thrown.
   *
   * @return The value of the queens on the board.
   */
  size_t valueQueens() const noexcept;

private:
  count_type mKings;
  count_type mQueens;
  count_type mRooks;
  count_type mBishops;
  count_type mKnights;
  count_type mPawns;
  count_type mTotal;
};

/**
 * Format a PieceCount for an output stream.
 *
 * @param os The output stream.
 * @param pc A PieceCount object.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceCount &pc);

/**
 * @function operator==
 * @brief Compares two PieceCount objects for equality.
 *
 * The function is guaranteed not to throw an exception.
 *
 * @param pc1 The first *PieceCount* object.
 * @param pc2 The second *PieceCount* object.
 * @return True if they are equal, false otherwise.
 */
bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept;

/**
 * @function operator!=
 * @brief Compares two PieceCount objects for non-equality.
 *
 * The function is guaranteed not to throw an exception.
 *
 * @param pc1 The first *PieceCount* object.
 * @param pc2 The second *PieceCount* object.
 * @return False if they are equal, true otherwise.
 */
bool operator!=(const PieceCount &pc1, const PieceCount &pc2) noexcept;

inline size_t PieceCount::valuePawns() const noexcept
{
  return static_cast<size_t>(mPawns) * static_cast<size_t>(PieceValue::PAWN);
}

inline size_t PieceCount::valueKnights() const noexcept
{
  return static_cast<size_t>(mKnights) * static_cast<size_t>(PieceValue::KNIGHT);
}

inline size_t PieceCount::valueBishops() const noexcept
{
  return static_cast<size_t>(mBishops) * static_cast<size_t>(PieceValue::BISHOP);
}

inline size_t PieceCount::valueRooks() const noexcept
{
  return static_cast<size_t>(mRooks) * static_cast<size_t>(PieceValue::ROOK);
}

inline size_t PieceCount::valueQueens() const noexcept
{
  return static_cast<size_t>(mQueens) * static_cast<size_t>(PieceValue::QUEEN);
}

} // namespace zoor

#endif 
