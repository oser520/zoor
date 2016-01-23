/**
 * @file piecemoves.hh
 * @author Omar A Serrano
 * @date 2015-12-29
 */
#ifndef _PIECEMOVES_H
#define _PIECEMOVES_H

#include <vector>
#include <iostream>

#include "piececode.hh"
#include "square.hh"

namespace zoor {

/**
 * TODO: implement thread safety
 * TODO: throw exceptions
 * TODO: implement operator[]
 */

/**
 * Maintains information about a move, including the destination square, if there's
 * a capture, and if there's a promotion (.i.e., the pawn moves to the last row and
 * becomes a more powerful piece).
 */
class PieceMove
{
  friend bool operator==(const PieceMove &pm1, const PieceMove &pm2);
  friend std::ostream operator<<(std::ostream &os, const PieceMove &pm);

public:

  /**
   * @brief Constructor with info for piece that is moving.
   * @param row The row of the piece that is moving.
   * @param column The column of the piece that is moving.
   * @param piece The piece that is moving.
   * @param color The color of the piece that is moving.
   * @throw Never throws.
   */
  PieceMove
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;

  /**
   * @brief Constructor with info for piece that is moving.
   * @param row The row of the piece that is moving.
   * @param column The column of the piece that is moving.
   * @param code The bit pattern containing the piece and color info.
   * @throw Never throws.
   */
  PieceMove(dim_type row, dim_type column, piececode_t code) noexcept;

  /**
   * @brief Default constructor.
   * @throw Never throws.
   */
  PieceMove() noexcept = default;

  /**
   * @brief Default copy constructor.
   * @param pieceMove The @c PieceMove being copied.
   * @throw Never throws.
   */
  PieceMove(const PieceMove &pieceMove) noexcept = default;

  /**
   * @brief Default move constructor.
   * @param pieceMove The @c PieceMove being moved.
   * @throw Never throws.
   */
  PieceMove(PieceMove &&pieceMove) noexcept = default;

  /**
   * @brief Default copy assignment.
   * @param pieceMove The @c PieceMove being copied.
   * @throw Never throws.
   */
  PieceMove& PieceMove(const PieceMove &pieceMove) noexcept = default;

  /**
   * @brief Default move assignment.
   * @param pieceMove The @c PieceMove being moved.
   * @throw Never throws.
   */
  PieceMove& PieceMove(PieceMove &&pieceMove) noexcept = default;

  /**
   * @brief Default destructor.
   * @throw Never throws.
   */
  ~PieceMove() noexcept = default;

  /**
   * @brief Obtain the row of source location.
   * @return The row of the source location.
   * @throw Never throws.
   */
  dim_type rowFrom() const noexcept;

  /**
   * @brief Obtain the column of the source location.
   * @return The column of the source location.
   * @throw Never throws.
   */
  dim_type columnFrom() const noexcept;

  /**
   * @brief Obtain the row of the destination square.
   * @return The row of the destination square.
   * @throw Never throws.
   */
  dim_type rowTo() const noexcept;

  /**
   * @brief Obtain the column of the destination square.
   * @return The column of the destination square.
   * @throw Never throws.
   */
  dim_type columnTo() const noexcept;

  /**
   * @brief Sets the information for the piece that is moving.
   * @param row The row location of the piece.
   * @param column The column location of the piece.
   * @param piece The piece.
   * @param color The color of the piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPiece
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;

  /**
   * @brief Sets the information for the piece that is moving.
   * @param row The row location of the piece.
   * @param column The column location of the piece.
   * @param code The bit pattern with color and piece info.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPiece(dim_type row, dim_type column, piececode_t code) noexcept;

  /**
   * @brief Obtain the information of the piece that is moving.
   * @return A @c Square representing the piece.
   * @throw Never throws.
   */
  Square piece() const noexcept;

  /**
   * @brief Sets the information for the catpured piece.
   * @param row The row location of the captured piece.
   * @param column The column location of the captured piece.
   * @param piece The piece captured.
   * @param color The color of the piece captured.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setCapture
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;

  /**
   * @brief Sets the information for the catpured piece.
   * @param row The row location of the captured piece.
   * @param column The column location of the captured piece.
   * @param code The bit code containing color and piece type information.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setCapture(dim_type row, dim_type column, piececode_t code) noexcept;

  /**
   * @brief Determine if the move has resulted in a capture.
   * @return True if the move has a capture, false otherwise.
   * @throw Never throws.
   */
  bool isCapture() const noexcept;

  /**
   * @brief Obtain the information for the captured piece.
   * @return The @c Square reprsenting the captured piece.
   * @throw Never throws.
   */
  Square capture() const noexcept;

  /**
   * @brief Sets the information for the promoted piece.
   * @param row The row location of the promoted piece.
   * @param column The column location of the promoted piece.
   * @param piece The piece obtained from the promotion.
   * @param color The color of the promoted piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromotion
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;

  /**
   * @brief Sets the color and piece for the promoted piece.
   * @param piece The piece obtained from the promotion.
   * @param color The color of the promoted piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromotion(PieceCode piece, PieceColor color) noexcept;

  /**
   * @brief Sets the color and piece for the promoted piece.
   * @param code The bit pattern containing the piece and color information.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromotion(piececode_t code) noexcept;

  /**
   * @brief Determine if the move has resulted in a promotion.
   * @return True if the move has a promotion, false otherwise.
   * @throw Never throws.
   */
  bool isPromotion() const noexcept;

  /**
   * @brief Obtain the information for the promoted piece.
   * @return The @c Square reprsenting the promoted piece.
   * @throw Never throws.
   */
  Square promotion() const noexcept;

private:
  /**
   * Represents the piece tha is making the move.
   */
  Square mFrom;

  /**
   * @brief Represents the location where the piece is moving to.
   * @detail If there is a capture, then the only time when <em>mDestination</em>
   *  and <em>mCapture</em> will not overlap is when a pawn is captured by
   *  <em>en passant</em>. If there is a pawn promotion, then <em>mDestination</em>
   *  will hold the information for the promoted piece.
   */
  Square mDestination;

  /**
   * Represents the location of the captured piece.
   */
  Square mCapture;
};

/**
 * @brief Equality operator for @c PieceMove.
 * @param pm1 The first @c PieceMove.
 * @param pm2 The second @c PieceMove.
 * @return True if the moves are equal, false otherwise.
 * @throw Never throws.
 */
bool operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept;

/**
 * @brief Non-equality operator for @c PieceMove.
 * @param pm1 The first @c PieceMove.
 * @param pm2 The second @c PieceMove.
 * @return True if the moves are not equal, false otherwise.
 * @throw Never throws.
 */
bool operator!=(const PieceMove &pm1, const PieceMove &pm2) noexcept;

/**
 * @brief Output operator for @c PieceMove.
 * @param os A reference to the output stream.
 * @param pm The @c PieceMove.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceMove &pm);

/**
 * @brief Represents the list of legal moves that are possible for a given piece from
 * a given square on a board.
 *
 * @c PieceMoves is aware of the piece type, the location in the board, and whether
 * a given move is legal.
 */
class PieceMoves
{
  friend std::ostream& operator<<(std::ostream&, const PieceMoves&);
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
  PieceMoves(const Square &square) noexcept;

  /**
   * Constructs @c PieceMoves with an <em>rvalue</em> @c Square.
   * @param square The @c Square used to initialize the piece making the moves. The
   *  piece cannot be <em>NONE</em>.
   * @throw Never throws exception.
   */
  PieceMoves(Square &&squre) noexcept;

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
  PieceMoves() = default;

  /**
   * @brief Copy constructor.
   * @param pieceMoves The @c PieceMoves being copied.
   * @throw Never throws exception.
   */
  PieceMoves(const PieceMoves &pieceMoves) noexcept = default;

  /**
   * @brief Move constructor.
   * @param pieceMoves The @c PieceMoves being moved.
   * @throw Never throws exception.
   */
  PieceMoves(PieceMoves &&pieceMoves) noexcept = default;

  /**
   * @brief Copy assignment.
   * @param pieceMoves The @c PieceMoves being copied.
   * @return A reference to this <tt>PieceMoves</tt>.
   */
  PieceMoves& operator=(const PieceMoves &pieceMoves) noexcept = default;

  /**
   * @brief Default constructor.
   * @param pieceMoves The @c PieceMoves being moved.
   * @return A reference to this <tt>PieceMoves</tt>.
   */
  PieceMoves& operator=(PieceMoves &&pieceMoves) noexcept = default;

  /**
   * @brief Destructor.
   * @throw Never throws exception.
   */
  ~PieceMoves() noexcept = default;

  /**
   * @brief Sets the piece that is making the moves.
   *
   * If this @c PieceMoves contains moves, and <em>pieces</em> is different than the
   * current piece, then the moves are clared.
   *
   * @param piece The piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setPiece(PieceCode piece) noexcept;

  /**
   * @brief Sets the piece color.
   *
   * If this @c PieceMoves contains moves, and <em>color</em> is different than the
   * current piece color, then the moves are clared.
   *
   * @param color The piece color.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setColor(PieceColor color) noexcept;

  /**
   * @brief Sets the row of the square for the piece making the moves.
   *
   * If this @c PieceMoves contains moves, and <em>row</em> is different than the
   * current row, then any moves that are not reachable from the new row are cleared.
   *
   * @param row The row of the squre for the piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setRow(dim_type row) noexcept;

  /**
   * @brief Sets the column of the square for the piece making the moves.
   *
   * If this @c PieceMoves contains moves, and <em>column</em> is different than the
   * current column, then any moves that are not reachable from the new column are
   * cleared.
   *
   * @param row The column of the squre for the piece making the moves.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setColumn(dim_type column) noexcept;

  /**
   * @brief Sets the @c Square of the piece making the moves.
   *
   * If this @c PieceMoves contains moves, then any move that is illegal from the new
   * @c Square is removed.
   *
   * @param square The square being copied.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setSquare(const Square &square) noexcept;

  /**
   * @brief Sets the @c Square of the piece making the moves.
   *
   * If this @c PieceMoves contains moves, then any move that is illegal from the new
   * @c Square is removed.
   *
   * @param square The square being moved.
   * @return A reference to this @c PieceMoves.
   * @throw Never throws exception.
   */
  PieceMoves& setSquare(Square &&square) noexcept;

  /**
   * @return The @c PieceCode value of the piece making the moves.
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

  /**
   * @return True if this @c PieceMoves does not contain any moves, false otherwise.
   * @throw Never throws exception.
   */
  bool empty() const noexcept;

  /**
   * @return The number of moves in this @c PieceMoves.
   * @throw Never throws exception.
   */
  size_type size() const noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return An iterator to the first move in this @c PieceMoves.
   * @throw Never throws exception.
   */
  iterator begin() noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return The off-the-end iterator to the list of moves in this @c PieceMoves.
   * @throw Never throws exception.
   */
  iterator end() noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return A constant iterator to the first move in this @c PieceMoves when it is
   *  <tt>const</tt>.
   * @throw Never throws exception.
   */
  const_iterator begin() const noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return The off-the-end iterator to the list of moves in this @c PieceMoves when
   *  it is <tt>const</tt>.
   * @throw Never throws exception.
   */
  const_iterator end() const noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return A constant iterator to the first move in this @c PieceMoves.
   * @throw Never throws exception.
   */
  const_iterator cbegin() noexcept;

  /**
   * @detail If there are no moves, then <tt>begin() == end()</tt>.
   * @return The constant off-the-end iterator to the list of moves in this
   *  @c PieceMoves.
   * @throw Never throws exception.
   */
  const_iterator cend() noexcept;

  /**
   * @brief Insert a @c Square to this @c PieceMoves.
   * @param square The @c Square being inserted.
   * @return A reference to this @c PieceMoves.
   * TODO: determine what kind of exception this can throw.
   */
  PieceMoves& push_back(const Square &square);

  /**
   * @brief Insert a @c Square to this @c PieceMoves.
   * @param square The @c Square being moved.
   * @return A reference to this @c PieceMoves.
   * TODO: determine what kind of exception this can throw.
   */
  PieceMoves& push_back(Square &&square);

  /**
   * @brief Remove a @c Square from this @c PieceMoves.
   * @return A reference to this @c PieceMoves.
   * TODO: determine what kind of exception this can throw.
   */
  PieceMoves& pop_back() noexcept;

  /**
   * @brief A copy of the last @c Square inserted into this @c PieceMoves.
   * @return A copy of the last move.
   * @throw Throws exception if there are no moves.
   * TODO: determine what kind of exception it throws
   */
  Square back() const;

  /**
   * @brief A copy of the first @c Square held in @c PieceMoves.
   * @return A copy of the first move.
   * @throw Throws exception if there are no moves.
   * TODO: determine what kind of exception it throws
   */
  Square front() const;

  /**
   * @brief Removes all the moves from this @c PieceMoves.
   * @return A reference to this @c PieceMoves.
   * TODO: determine what kind of exception this can throw.
   */
  PieceMoves& clear();

  // TODO: add emplace_back
};

/**
 * @brief Output operator for @c PieceMoves.
 * @detail Format is (Square, (Move1, Move2, ..., MoveN)), where @c Square represents
 *  the piece making the moves, and <em>Move1</em> through <em>MoveN</em> represent
 *  the list of moves, each of which is a @c Square. If there are no moves, then the
 *  list is empty.
 * @param os The output stream.
 * @param pm The @c PieceMoves.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream &os, const PieceMoves &pm);

/**
 * @brief Equality operator for @c PieceMoves.
 * @param pm1 The first @c PieceMoves.
 * @param pm2 The second @c PieceMoves.
 * @return True if pm1 and pm2 are equal, false otherwise.
 */
bool operator==(const PieceMoves &pm1, const PieceMoves &pm2) noexcept;

/**
 * @brief Non-equality operator for @c PieceMoves.
 * @param pm1 The first @c PieceMoves.
 * @param pm2 The second @c PieceMoves.
 * @return True if pm1 and pm2 are different, false otherwise.
 */
bool operator!=(const PieceMoves &pm1, const PieceMoves &pm2) noexcept;

} // namespace zoor

#endif // _PIECEMOVES_H
