/////////////////////////////////////////////////////////////////////////////////////
/// @file basicboard.hh
/// @author Omar A Serrano
/// @date 2016-04-28
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BASICBOARD_H
#define _BASICBOARD_H

//
// zoor
//
#include "piececode.hh"

namespace zoor {

///
/// @brief A simple board that represents the position in a chess board.
///
class BasicBoard:
{
public:
  ///
  /// @brief The number of squares in the @c SimpleBoard.
  ///
  static constexpr size_t SIZE = 64;

  ///
  /// @brief Default ctor.
  /// @details Initializes the board with the normal setup for beginning game.
  /// @throw May throw bad memory allocation.
  ///
  BasicBoard();

  ///
  /// @brief Copy ctor.
  /// @param board The @c SimpleBoard to be copied.
  /// @throw May throw bad memory allocation.
  ///
  BasicBoard(const BasicBoard &board);

  ///
  /// @brief Move ctor.
  /// @param board The @c SimpleBoard being moved.
  /// @throw Never throws.
  ///
  BasicBoard(BasicBoard &&board) noexcept;

  ///
  /// @brief Copy assignment.
  /// @param board The @c SimpleBoard being assigned.
  /// @return A reference to @c BasicBoard.
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(const BasicBoard &board) noexcept;

  ///
  /// @brief Move assignment.
  /// @param board The @c SimpleBoard being moved.
  /// @return A reference to @c BasicBoard.
  /// @throw Never throws.
  ///
  BasicBoard&
  operator=(BasicBoard &&board) noexcept;

  ///
  /// @brief Dtor.
  /// @throw Never throws.
  ///
  ~BasicBoard() noexcept;

  ///
  /// @brief Obtain the contents of a given square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @return The piece located at the given square.
  /// @throw Never throws.
  /// TODO: define dim_t in basictypes.hh
  ///
  piece_t
  get(dim_t row, dim_t column) noexcept;

  ///
  /// @brief Put a chess piece on a square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @param piece The type of chess piece.
  /// @throw Never throws.
  /// TODO: define piece_t in basictypes.hh
  ///
  void
  put(dim_t row, dim_t column, piece_t piece) noexcept;

  ///
  /// @brief Put a chess piece on a square.
  /// @param row The row of the square.
  /// @param column The column of the square.
  /// @param piece The type of chess piece.
  /// @param color The color of the chess piece.
  /// @throw Never throws.
  /// TODO: redefine PieceCode as Piece and PieceColor as Color.
  ///
  void
  put(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @brief Get iterator to the first square on the board.
  /// @throw Never throws.
  ///
  iterator
  begin() const noexcept;

  ///
  /// @brief Get iterator to one past the last square.
  /// @throw Never throws.
  ///
  iterator
  end() const noexcept;

private:
  // pointer to the array
  piece_t *mArr;
};

} // zoor
#endif // _BASICBOARD_H
