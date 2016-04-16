/**
 * @file piececount.hh
 * @author Omar A Serrano
 * @date 2015-12-19
 */

#ifndef _PIECECOUNT_H
#define _PIECECOUNT_H

#include <iostream>
#include <vector>
#include <stdexcept>

#include "square.hh"
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

  /// @brief Constructor with a @c Board.
  /// @param board The board whose pieces are counted.
  /// @throw Never throws.
  PieceCount(const Board &board) noexcept;

  /// @brief Constructor with a list of squares.
  /// @param squareList The list of squres with pieces.
  /// @throw Never throws.
  PieceCount(const std::vector<Square> &squareList) noexcept;

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

  /// @brief Count the number of pieces in board.
  /// @param board The board whose pieces are counted.
  /// @return A reference to this PieceCount.
  /// @throw Never throws.
  PieceCount& count(const Board &board) noexcept;

  /// @brief Count the number of pieces in a list of @c Squares.
  /// @param squareList A list of @c Squares with pieces.
  /// @return A reference to this PieceCount.
  /// @throw Never throws.
  PieceCount& count(const std::vector<Square> &squareList) noexcept;

  /// @brief Checks that invariants hold.
  /// @return True if invariants hold, false otherwise.
  /// @throw Never throws.
  const bool good() const noexcept;

  /// @brief Sets the count of every piece to zero.
  /// @return A reference to this PieceCount.
  /// @throw Never throws.
  PieceCount& clear() noexcept;

  /// @brief Get number of white kings.
  /// @return The number of white kings.
  /// @throw Never throws.
  const count_type wKing() const noexcept;

  /// @brief Get the number of white queens.
  /// @return The number of white queens.
  /// @throw Never throws.
  const count_type wQueen() const noexcept;

  /// @brief Get the number of white rooks.
  /// @return The number of white rooks.
  /// @throw Never throws.
  const count_type wRook() const noexcept;

  /// @brief Get the number of white bishops.
  /// @return The number of white bishops.
  /// @throw Never throws.
  const count_type wBishop() const noexcept;

  /// @brief Get the number of white knights.
  /// @return The number of white knights.
  /// @throw Never throws.
  const count_type wKnight() const noexcept;

  /// @brief Get the number of white pawns.
  /// @return The number of white pawns.
  /// @throw Never throws.
  const count_type wPawn() const noexcept;

  /// @brief Get number of black kings.
  /// @return The number of black kings.
  /// @throw Never throws.
  const count_type bKing() const noexcept;

  /// @brief Get the number of black queens.
  /// @return The number of black queens.
  /// @throw Never throws.
  const count_type bQueen() const noexcept;

  /// @brief Get the number of black rooks.
  /// @return The number of black rooks.
  /// @throw Never throws.
  const count_type bRook() const noexcept;

  /// @brief Get the number of black bishops.
  /// @return The number of black bishops.
  /// @throw Never throws.
  const count_type bBishop() const noexcept;

  /// @brief Get the number of black knights.
  /// @return The number of black knights.
  /// @throw Never throws.
  const count_type bKnight() const noexcept;

  /// @brief Get the number of black pawns.
  /// @return The number of black pawns.
  /// @throw Never throws.
  const count_type bPawn() const noexcept;

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
// default Ctor
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

//
// get the number of white kings
//
inline const count_type
PieceCount::wKing() const noexcept
{
  return (mWhite >> KSHIFT) & CMASK;
}

//
// get the number of white queens
//
inline const count_type
PieceCount::wQueen() const noexcept
{
  return (mWhite >> QSHIFT) & CMASK;
}

//
// get the number of white rooks
//
inline const count_type
PieceCount::wRook() const noexcept
{
  return (mWhite >> RSHIFT) & CMASK;
}

//
// get the number of white bishops
//
inline const count_type
PieceCount::wBishop() const noexcept
{
  return (mWhite >> BSHIFT) & CMASK;
}

//
// get the number of white knights
//
inline const count_type
PieceCount::wKnight() const noexcept
{
  return (mWhite >> NSHIFT) & CMASK;
}

//
// get the number of white pawns
//
inline const count_type
PieceCount::wPawn() const noexcept
{
  return (mWhite >> PSHIFT) & CMASK;
}

//
// get the number of black kings
//
inline const count_type
PieceCount::bKing() const noexcept
{
  return (mBlack >> KSHIFT) & CMASK;
}

//
// get the number of black queens
//
inline const count_type
PieceCount::bQueen() const noexcept
{
  return (mBlack >> QSHIFT) & CMASK;
}

//
// get the number of black rooks
//
inline const count_type
PieceCount::bRook() const noexcept
{
  return (mBlack >> RSHIFT) & CMASK;
}

//
// get the number of black bishops
//
inline const count_type
PieceCount::bBishop() const noexcept
{
  return (mBlack >> BSHIFT) & CMASK;
}

//
// get the number of black knights
//
inline const count_type
PieceCount::bKnight() const noexcept
{
  return (mBlack >> NSHIFT) & CMASK;
}

//
// get the number of black pawns
//
inline const count_type
PieceCount::bPawn() const noexcept
{
  return (mBlack >> PSHIFT) & CMASK;
}

} // namespace zoor

#endif 
