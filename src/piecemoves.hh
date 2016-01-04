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

  /**
   * Constructs @c PieceMoves with a @c Square.
   * @param square The @c Square used to initialize the piece making the moves. The
   *  piece cannot be <em>NONE</em>.
   * @throw Never throws exception.
   */
  PieceMoves(const Square& square) noexcept;

  /**
   * Constructs @c PieceMoves with an <em>rvalue</em> @c Square.
   * @param square The @c Square used to initialize the piece making the moves. The
   *  piece cannot be <em>NONE</em>.
   * @throw Never throws exception.
   */
  PieceMoves(Square&&) noexcept;

  /**
   * @brief Constructs @c PieceMoves with the four paramters used to construct a
   * @c Square.
   * @param row The row of the @c Square.
   * @param column The column of the @c Square.
   * @param piece The piece making the moves. The piece cannot be <em>NONE</em>.
   * @param color The color of the piece.
   * @throw Never throws exception.
   */
  PieceMoves
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;
  
  
  /**
   * @brief Default constructor.
   * @throw Never throws exception.
   */
  PieceMoves() noexcept;

  /**
   * @brief Copy constructor.
   * @param pieceMoves The @c PieceMoves being copied.
   * @throw Never throws exception.
   */
  PieceMoves(const PieceMoves &pieceMoves);

  /**
   * @brief Move constructor.
   * @param pieceMoves The @c PieceMoves being moved.
   * @throw Never throws exception.
   */
  PieceMoves(PieceMoves &&pieceMoves) noexcept;

  /**
   * @brief Copy assignment.
   * @param pieceMoves The @c PieceMoves being copied.
   * @return A reference to this <tt>PieceMoves</tt>.
   */
  PieceMoves& operator=(const PieceMoves &pieceMoves);

  /**
   * @brief Default constructor.
   * @param pieceMoves The @c PieceMoves being moved.
   * @return A reference to this <tt>PieceMoves</tt>.
   */
  PieceMoves& operator=(PieceMoves &&pieceMoves) noexcept;

  /**
   * @brief Destructor.
   * @throw Never throws exception.
   */
  ~PieceMoves() noexcept = default;

  /**
   * @brief Sets the piece that is making the moves.
   * @param piece The piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setPiece(PieceCode piece) noexcept;

  /**
   * @brief Sets the piece color.
   * @param color The piece color.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setColor(PieceColor color) noexcept;

  /**
   * @brief Sets the row of the square for the piece making the moves.
   * @param row The row of the squre for the piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setRow(dim_type row) noexcept;

  /**
   * @brief Sets the column of the square for the piece making the moves.
   * @param row The column of the squre for the piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setColumn(dim_type column) noexcept;

  /**
   * @brief Sets the @c Square of the piece making the moves.
   * @param square The square being copied.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setSquare(const Square &square) noexcept;

  /**
   * @brief Sets the @c Square of the piece making the moves.
   * @param square The square being moved.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setSquare(Square &&square) noexcept;

  /**
   * @brief Gets the piece making the moves.
   * @return The @c PieceCode value of the piece.
   * @throw Never throws exception.
   */
  PieceCode piece() const noexcept;

  /**
   * @return The @c PieceColor of the piece.
   * @throw Never throws exception.
   */
  PieceColor color() const noexcept;

  /**
   * @return The row of the square of the piece making the moves.
   * @throw Never throws exception.
   */
  dim_type row() const noexcept;

  /**
   * @brief Gets the column of the square of the piece making the moves.
   * @return row The column of the square of the piece making the moves.
   * @throw Never throws exception.
   */
  dim_type column() const noexcept;

  /**
   * @return The @c Squre of the piece making the moves.
   * @throw Never throws exception.
   */
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
