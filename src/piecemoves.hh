/**
 * @file piecemoves.hh
 * @author Omar A Serrano
 * @date 2015-12-29
 */
#ifndef _PIECEMOVES_H
#define _PIECEMOVES_H

#include <vector>
#include <iostream>
#include <memory>

#include "square.hh"

namespace zoor {

/**
 * @brief Represents the list of legal moves that are possible for a given piece from
 * a given square on a board.
 *
 * @c PieceMoves is aware of the piece type, the location in the board, and whether
 * a given move is legal.
 */
class PieceMoves
{
  friend std::ostream& operator<<(std::ostream&, const PieceMoves&) noexcept;
  friend bool operator==(const PieceMoves&, const PieceMoves&) noexcept;

  /**
   * The @c Square from which the moves are made.
   *
   * The @c Square holds information about the row and column in the board, the
   * piece type, and the piece color. This is the piece that is making the moves.
   */
  Square mSquare;

  /**
   * A list of moves, each of which is represented by a @c Square.
   *
   * Each @c Square represents a legal move for the piece. If the move captures a
   * piece, then the @c Square contains the piece.
   */
  std::vector<Square> mMoves;

public:
  /**
   * Iterator for a @c Square @c vector.
   */
  using iterator = std::vector<Square>::iterator;

  /**
   * Iterator for a @c const @c Square @c vector.
   */
  using const_iterator = std::vector<Square>::const_iterator;

  /**
   * Alias for the size type of a @c Square @c vector.
   */
  using size_type = std::vector<Square>::size_type;

  /**
   * Alias for the dimension type of a @c Square.
   */
  using dim_type = Square::dim_type;

  // custom constructors
  PieceMoves(const Square&) noexcept;
  PieceMoves(Square&&) noexcept;
  PieceMoves(dim_type row, dim_type column, PieceCode piece, PieceColor color) noexcept;
  
  // standard copy control
  PieceMoves() noexcept;
  PieceMoves(const PieceMoves&);
  PieceMoves(PieceMoves&&) noexcept;
  PieceMoves& operator=(const PieceMoves&);
  PieceMoves& operator=(PieceMoves &&) noexcept;
  ~PieceMoves() noexcept = default;

  // interface
  PieceMoves& setPiece(PieceCode) noexcept;
  PieceMoves& setColor(PieceColor) noexcept;
  PieceMoves& setRow(dim_type) noexcept;
  PieceMoves& setColumn(dim_type) noexcept;
  PieceMoves& setSquare(Square) noexcept;

  PieceCode piece() const noexcept;
  PieceColor color() const noexcept;
  dim_type row() const noexcept;
  dim_type column() const noexcept;
  Square square() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;

  // iterator access
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() noexcept;
  const_iterator cend() noexcept;

  // adding and removing Square elements
  PieceMoves& push_back(const Square&);
  PieceMoves& pop_back();
  Square top();
  PieceMoves& clear();

  // TODO: add emplace_back
};

} // namespace zoor

#endif // _PIECEMOVES_H
