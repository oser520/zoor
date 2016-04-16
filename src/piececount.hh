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

  /// @brief Get number of white kings.
  /// @return The number of white kings.
  /// @throw Never throws.
  count_type wKing() const noexcept;

  /// @brief Get the number of white queens.
  /// @return The number of white queens.
  /// @throw Never throws.
  count_type wQueen() const noexcept;

  /// @brief Get the number of white rooks.
  /// @return The number of white rooks.
  /// @throw Never throws.
  count_type wRook() const noexcept;

  /// @brief Get the number of white bishops.
  /// @return The number of white bishops.
  /// @throw Never throws.
  count_type wBishop() const noexcept;

  /// @brief Get the number of white knights.
  /// @return The number of white knights.
  /// @throw Never throws.
  count_type wKnight() const noexcept;

  /// @brief Get the number of white pawns.
  /// @return The number of white pawns.
  /// @throw Never throws.
  count_type wPawn() const noexcept;

private:
  // Mantain the count of white and black pieces.
  count_type mWhite;
  count_type mBlack;

  // bit shifting counts for pieces
  enum CountShift: count_type {
    PSHIFT = 5 * 0,
    NSHIFT = 5 * 1,
    BSHIFT = 5 * 2,
    RSHIFT = 5 * 3,
    QSHIFT = 5 * 4,
    KSHIFT = 5 * 5
  };

  // 5 bit mask
  enum CountMask: count_type {
    CMASK = 0x1f
  }
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

} // namespace zoor

#endif 
