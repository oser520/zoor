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

public:
  // typedefs
  using iterator = std::vector<MoveTo>::iterator;
  using const_iterator = std::vector<MoveTo>::const_iterator;
  using size_type = std::vector<MoveTo>::size_type;

  // custom constructors
  PieceMoves(PieceColor, PieceCode, Square);
  PieceMoves(PieceColor, PieceCode, Square, std::vector<MoveTo>);
  
  // standard copy control
  PieceMoves();
  PieceMoves(const PieceMoves&);
  PieceMoves(PieceMoves&&) = default;
  PieceMoves& operator=(const PieceMoves&) = default;
  PieceMoves& operator=(PieceMoves &&) = default;
  ~PieceMoves() noexcept = default;

  // interface
  PieceMoves& setColor(PieceColor) noexcept;
  PieceMoves& setPiece(PieceCode) noexcept;
  PieceMoves& setSquare(Square) noexcept;

  PieceColor color() const noexcept;
  PieceCode piece() const noexcept;
  Square square(Square) const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;

  // iterator access
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() noexcept;
  const_iterator cend() noexcept;

  // adding and removing MoveTo elements
  PieceMoves& push_back(const MoveTo&);
  PieceMoves& pop_back();
  PieceMoves& clear();

  // TODO: add emplace_back

private:
  Square mSquare;
  std::vector<MoveTo> mMoves;

public:
  /**
   * A move to a given position.
   */
  class MoveTo
  {
    friend std::ostream& operator<<(std::ostream&, const MoveTo&);
    friend bool operator==(const MoveTo&, const MoveTo&) noexcept;
    friend class PieceMoves;

  private:
    PieceColor mColor;
    PieceCode mPiece;
    Square mSquare;
    unique_ptr<PieceMoves> mParent;

  public:
    /* copy control */
    MoveTo() = default;
    MoveTo(PieceColor, PieceCode, const Square&) = default;
    MoveTo(PieceColor, PieceCode, Square&&) = default;
    MoveTo(const MoveTo&) = default;
    MoveTo(MoveTo&&) noexcept = default;
    MoveTo& operator=(const MoveTo&) = default;
    MoveTo& operator=(MoveTo&&) noexcept = default;
    ~MoveTo() noexcept = default;

    /* getters */
    PieceColor color() const noexcept;
    PieceCode piece() const noexcept;
    Square square() const noexcept;

    // TODO: implement as template with universal paramter T&&
    // setters with lvalue paramters
    MoveTo& setColor(const PieceColor&) noexcept;
    MoveTo& setPiece(const PieceCode&) noexcept;
    MoveTo& setSquare(const Square&) noexcept;

    // implement as template with universal paramter T&&
    // setters with rvalue paramters
    MoveTo& setColor(PieceColor&&) noexcept;
    MoveTo& setPiece(PieceCode&&) noexcept;
    MoveTo& setSquare(Square&&) noexcept;
  };
};

} // namespace zoor

#endif // _PIECEMOVES_H
