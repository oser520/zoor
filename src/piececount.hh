/**
 * @file piececount.hh
 * @author Omar A Serrano
 * @date 2015-12-19
 */

#ifndef _PIECECOUNT_H
#define _PIECECOUNT_H

#include <iostream>
#include <stdexcept>

#include "board.hh"
#include "piececode.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// Declarations
/////////////////////////////////////////////////////////////////////////////////////

/// @brief PieceCount counts the number of pieces on a board.
/// @details Maintains the following invariants:
/// @li At least one king, and no more than two kings.
/// @li No more than 8 pawns per player.
/// @li No more than 10 pieces of type knight, bishop, or rook.
/// @li No more than 9 queen.
/// @li No more than 16 pieces total per player.

class PieceCount
{
  friend bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept;
  friend std::ostream& operator<<(std::ostream &os, const PieceCount &pc);

public:
  /// @brief The type used to count pieces.
  using count_type = uint32_t;

  /// @brief Default ctor.
  /// @details Initializes count to 0 for all pieces.
  PieceCount() noexcept;

  /// @brief Copy constructor.
  /// @param pcount The @c PieceCount to be copied.
  /// @throw Never throws.
  PieceCount(const PieceCount &pcount) noexcept = default;

  /// @brief Move constructor.
  /// @param pcount The @c PieceCount to be moved.
  /// @throw Never throws.
  PieceCount(PieceCount &&pcount) noexcept = default;

  /// @brief Copy assignment operator.
  /// @param pcount The @c PieceCount to be copied.
  /// @return A reference to this @c PieceCount.
  /// @throw Never throws.
  PieceCount& operator=(const PieceCount &pcount) noexcept = default;

  /// @brief Move assignment operator.
  /// @param pcount The @c PieceCount to be moved.
  /// @return A reference to this @c PieceCount.
  /// @throw Never throws.
  PieceCount& operator=(PieceCount &&pcount) noexcept = default;

  /// @brief Default destructor.
  /// @throw Never throws.
  ~PieceCount() noexcept = default;

  /// @brief Sets the count of every piece to zero.
  /// @return A reference to this PieceCount.
  /// @throw Never throws.
  PieceCount& clear() noexcept;

  /// @brief Decreases the count for a given piece by one.
  /// @detail Won't decrease the count of a given piece below zero.
  /// @param piece The @c PieceCode with count being decreased.
  /// @return The new count for the piece.
  /// @throw Never throws.
  count_type minus(PieceCode piece) noexcept;

  /// @brief Decreases the count for a given piece by a given value.
  /// @detail Won't decrease the count of a given piece below zero.
  /// @param piece The @c PieceCode with count being decreased.
  /// @param value The value by which the count of the piece is being decreased.
  /// @return The new count for the piece.
  /// @throw Never throws.
  count_type minus(PieceCode piece, count_type value) noexcept;

  /// @brief Sets the count for a given piece.
  /// @detail Won't set value below zero.
  /// @param piece The @c PieceCode for the piece's count being set.
  /// @param value The value of the count for the piece.
  /// @return A reference to this @c PieceCount.
  /// @throw Never throws.
  PieceCount& setCount(PieceCode piece, count_type value) noexcept;

  /// @brief Get the piece count for kings.
  /// @return A copy of the count for kings.
  /// @throw Never throws.
  count_type kings() const noexcept { return mKings; }

  /// @brief Get the piece count for queens.
  /// @return A copy of the count for queens.
  /// @throw Never throws.
  count_type queens() const noexcept { return mQueens; }

  /// @brief Get the piece count for rooks.
  /// @return A copy of the count for rooks.
  /// @throw Never throws.
  count_type rooks() const noexcept { return mRooks; }

  /// @brief Get the piece count for bishops.
  /// @return A copy of the count for bishops.
  /// @throw Never throws.
  count_type bishops() const noexcept { return mBishops; }

  /// @brief Get the piece count for knights.
  /// @return A copy of the count for knights.
  /// @throw Never throws.
  count_type knights() const noexcept { return mKnights; }

  /// @brief Get the piece count for pawns.
  /// @return A copy of the count for pawns.
  /// @throw Never throws.
  count_type pawns() const noexcept { return mPawns; }

  /// @brief Obtain the value of the pawns on the board.
  /// @details The value of the pawns on the board is simply the number of pawns
  /// times the value of each pawn. The object is not modified and no exceptions are
  /// thrown.
  /// @return The value of the pawns on the board.
  size_t valuePawns() const noexcept;

  /// @brief Obtain the value of the knights on the board.
  /// @details The value of the knights on the board is simply the number of knights
  /// times the value of each knight. The object is not modified and no exceptions
  /// are thrown.
  /// @return The value of the knights on the board.
  size_t valueKnights() const noexcept;

  /// @brief Obtain the value of the bishops in the board.
  /// @details The value of the bishops on the board is simply the number of bishops
  /// times the value of each bishop. The object is not modified and no exceptions
  /// are thrown.
  /// @return The value of the bishops on the board.
  size_t valueBishops() const noexcept;

  /// @brief Obtain the value of the rooks in the board.
  /// @details The value of the rooks on the board is simply the number of rooks
  /// times the value of each rook. The object is not modified and no exceptions are
  /// thrown.
  /// @return The value of the rooks on the board.
  size_t valueRooks() const noexcept;

  /// @brief Obtain the value of the queens in the board.
  /// @details The value of the queens on the board is simply the number of queens
  /// times the value of each queen. The object is not modified and no exceptions are
  /// thrown.
  /// @return The value of the queens on the board.
  size_t valueQueens() const noexcept;

private:
  // Mantain the count of white and black pieces.
  count_type mWhite;
  count_type mBlack;

  // bit shifting counts for pieces
  enum CountShift {
    PSHIFT = 5 * 0,
    NSHIFT = 5 * 1,
    BSHIFT = 5 * 2,
    RSHIFT = 5 * 3,
    QSHIFT = 5 * 4,
    KSHIFT = 5 * 5
  };
};

/// @breief Format a PieceCount for an output stream.
/// @param os The output stream.
/// @param pc A PieceCount object.
/// @return A reference to the output stream.
std::ostream& operator<<(std::ostream &os, const PieceCount &pc);

/// @brief Compares two PieceCount objects for equality.
/// @param pc1 The first *PieceCount* object.
/// @param pc2 The second *PieceCount* object.
/// @return True if they are equal, false otherwise.
/// @throw Never throws.
bool operator==(const PieceCount &pc1, const PieceCount &pc2) noexcept;

/// @brief Compares two PieceCount objects for non-equality.
/// @param pc1 The first *PieceCount* object.
/// @param pc2 The second *PieceCount* object.
/// @return False if they are equal, true otherwise.
/// @throw Never throws.
bool operator!=(const PieceCount &pc1, const PieceCount &pc2) noexcept;

/////////////////////////////////////////////////////////////////////////////////////
// Inline definitions
/////////////////////////////////////////////////////////////////////////////////////

//
// Defualt Ctor
//
PieceCount::PieceCount()
  : mWhite(),
    mBlack() {}

//
// clear the piece count for each piece
//
PieceCount& PieceCount::clear() noexcept
{
  mWhite = mBlack = 0;
  return *this;
}


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
