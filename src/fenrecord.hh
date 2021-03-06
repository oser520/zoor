////////////////////////////////////////////////////////////////////////////////
//! @file fenrecord.hh
//! @author Omar A Serrano
//! @date 2016-04-17
//! @details Class declaration for a Forsyth-Edwards Notation (FEN) record.
////////////////////////////////////////////////////////////////////////////////
#ifndef _FENRECORD_H
#define _FENRECORD_H

//
// STL headers
//
#include <cassert>
#include <cstdint>
#include <memory>

namespace zoor {

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

// forward declaration
class Board;

//! @brief Aggregates the information in a Forsyth-Edwards (FEN) record.
//! @details The information in the first four fields of a FEN record are
//! embedded within a @c Board, but the last two fields are not, because they
//! represent information that should be maintained by the @c Player. In other
//! words, a @c Board doesn't care about the number of moves, but a @c Player
//! does.
class FenRecord
{
public:
  //! @brief Alias for shared pointer to @c Board.
  using board_ptr = std::shared_ptr<Board>;

  //
  // No default ctor
  //
  FenRecord() = delete;

  //! @brief Initializes a FenRecord with a pointer to a board, the half move
  //! count, and the full move count.
  //! @param pBoard A shared pointer to a board.
  //! @param hMove The half move count.
  //! @param fMove The full move count.
  //! @throw Never throws.
  FenRecord(const board_ptr &pBoard, size_t hMove, size_t fMove) noexcept;

  //! @brief Default copy ctor.
  //! @param fenRecord The @c FenRecord being copied.
  //! @throw Never throws.
  FenRecord(const FenRecord &fenRecord) noexcept = default;

  //! @brief Default move ctor.
  //! @param fenRecord The @c FenRecord being moved.
  //! @throw Never throws.
  FenRecord(FenRecord &&fenRecord) noexcept = default;

  //! @brief Default copy assignment.
  //! @param fenRecord The @c FenRecord being copied.
  //! @throw Never throws.
  FenRecord&
  operator=(const FenRecord &fenRecord) noexcept = default;

  //! @brief Default move assignment.
  //! @param fenRecord The @c FenRecord being moved.
  //! @throw Never throws.
  FenRecord&
  operator=(FenRecord &&fenRecord) noexcept = default;

  //! @brief Default dtor.
  //! @throw Never throws.
  ~FenRecord() noexcept = default;

  //! @brief Get the number of half moves.
  //! @return The number of half moves.
  //! @throw Never throws.
  size_t
  halfMove() const noexcept;

  //! @brief Get the number of full moves.
  //! @return The number of full moves.
  //! @throw Never throws.
  size_t
  fullMove() const noexcept;

  //! @brief Get the pointer to the board.
  //! @return The pointer to the board.
  //! @throw Never throws.
  board_ptr
  boardPtr() const noexcept;

private:
  uint16_t mHalfMove;
  uint16_t mFullMove;
  board_ptr mBoardPtr;
};

////////////////////////////////////////////////////////////////////////////////
// inline function definitions
////////////////////////////////////////////////////////////////////////////////

//
// initializer
//
inline FenRecord::
FenRecord(const board_ptr &pBoard, size_t hMove, size_t fMove) noexcept
  : mHalfMove(hMove),
    mFullMove(fMove),
    mBoardPtr(pBoard)
{
  assert(mBoardPtr != nullptr);
}

//
// get the half move count
//
inline size_t
FenRecord::halfMove() const noexcept
{
  return mHalfMove;
}

//
// get the full move count
//
inline size_t
FenRecord::fullMove() const noexcept
{
  return mFullMove;
}

//
// get the pointer to the board
//
inline FenRecord::board_ptr
FenRecord::boardPtr() const noexcept
{
  return mBoardPtr;
}

} // namespace zoor
#endif // _FENRECORD_H
