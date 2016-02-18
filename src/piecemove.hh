/**
 * @file piecemove.hh
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
 * Maintains information about a move, including the destination square, if there's
 * a capture, and if there's a promotion (.i.e., the pawn moves to the last row and
 * becomes a more powerful piece).
 */
class PieceMove
{
  friend bool operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept;
  friend std::ostream& operator<<(std::ostream &os, const PieceMove &pm);

public:
  /**
   * Alias for the type of the dimension of the board.
   */
  using dim_type = short;

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
   * @brief Constructor with info for piece that is moving, and where it is moving.
   * @param fromRow The row from where the piece is moving.
   * @param fromColumn The column from where the piece is moving.
   * @param code The bit pattern containing the piece and color info.
   * @param toRow The row where the piece is moving.
   * @param toColumn The column where the piece is moving.
   * @throw Never throws.
   */
  PieceMove
    (dim_type fromRow,
     dim_type fromColumn,
     piececode_t code,
     dim_type toRow,
     dim_type toColumn) noexcept;

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
  dim_type fromRow() const noexcept;

  /**
   * @brief Obtain the column of the source location.
   * @return The column of the source location.
   * @throw Never throws.
   */
  dim_type fromColumn() const noexcept;

  /**
   * @brief Obtain the row of the destination square.
   * @return The row of the destination square.
   * @throw Never throws.
   */
  dim_type toRow() const noexcept;

  /**
   * @brief Obtain the column of the destination square.
   * @return The column of the destination square.
   * @throw Never throws.
   */
  dim_type toColumn() const noexcept;

  /**
   * @brief Obtain the row of captured piece.
   * @return The row of the captured piece.
   * @throw Never throws.
   */
  dim_type captureRow() const noexcept;

  /**
   * @brief Obtain the column of the captured piece.
   * @return The column of the captured piece.
   * @throw Never throws.
   */
  dim_type captureColumn() const noexcept;

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
   * @brief Sets the color and piece for the piece that is moving.
   * @param piece The piece that is moving.
   * @param color The color of the piece that is moving.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPiece(PieceCode piece, PieceColor color) noexcept;

  /**
   * @brief Sets the color and piece for the piece that is moving.
   * @param code The bit code for the piece and piece color.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPiece(piececode_t code) noexcept;

  /**
   * @brief Obtain the information of the piece that is moving.
   * @return A @c Square representing the piece.
   * @throw Never throws.
   */
  Square fromSquare() const noexcept;

  /**
   * @brief Get the @c PieceCode of the piece that is moving.
   * @return The @c PieceCode of the piece making the move.
   * @throw Never throws.
   */
  PieceCode fromPiece() const noexcept;

  /**
   * @brief Get the @c PieceColor of the piece that is moving.
   * @return The @c PieceColor of the piece making the move.
   * @throw Never throws.
   */
  PieceColor fromColor() const noexcept;

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
   * @brief Sets the piece and color for the catpured piece.
   * @param piece The piece type of the captured piece.
   * @param color The color of the captured piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setCapture(PieceCode piece, PieceColor color) noexcept;

  /**
   * @brief Sets the piece and color for the catpured piece.
   * @param code The bit code for the piece and color of the captured piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setCapture(piececode_t code) noexcept;

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
  Square captureSquare() const noexcept;

  /**
   * @brief Obtain the captured @c PieceCode.
   * @return The @c PieceCode for the captured piece.
   * @throw Never throws.
   */
  PieceCode capturePiece() const noexcept;

  /**
   * @brief Obtain the captured @c PieceColor.
   * @return The @c PieceColor for the captured piece.
   * @throw Never throws.
   */
  PieceColor captureColor() const noexcept;

  /**
   * @brief Sets the information for the promoted piece.
   * @param row The row location of the promoted piece.
   * @param column The column location of the promoted piece.
   * @param piece The piece obtained from the promotion.
   * @param color The color of the promoted piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromo
    (dim_type row,
     dim_type column,
     PieceCode piece,
     PieceColor color) noexcept;

  /**
   * @brief Sets the information for the promoted piece.
   * @param row The row location of the promoted piece.
   * @param column The column location of the promoted piece.
   * @param code The piece obtained from the promotion.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromo
    (dim_type row,
     dim_type column,
     piececode_t code) noexcept;

  /**
   * @brief Sets the color and piece for the promoted piece.
   * @param piece The piece obtained from the promotion.
   * @param color The color of the promoted piece.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromo(PieceCode piece, PieceColor color) noexcept;

  /**
   * @brief Sets the color and piece for the promoted piece.
   * @param code The bit pattern containing the piece and color information.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setPromo(piececode_t code) noexcept;

  /**
   * @brief Determine if the move has resulted in a promotion.
   * @return True if the move has a promotion, false otherwise.
   * @throw Never throws.
   */
  bool isPromo() const noexcept;

  /**
   * @brief Obtain the information for the promoted piece.
   * @return The @c Square reprsenting the promoted piece.
   * @throw Never throws.
   */
  Square promoSquare() const noexcept;

  /**
   * @brief Obtain the promoted @c PieceCode.
   * @return The @c PieceCode for the promoted piece.
   * @throw Never throws.
   */
  PieceCode promoPiece() const noexcept;

  /**
   * @brief Obtain the promoted @c PieceColor.
   * @return The @c PieceColor for the promoted piece.
   * @throw Never throws.
   */
  PieceColor promoColor() const noexcept;

  /**
   * @brief Set the destination row.
   * @param row The destination row.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setToRow(dim_type row) noexcept;

  /**
   * @brief Set the destination column.
   * @param column The destination column.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setToColumn(dim_type column) noexcept;

  /**
   * @brief Set the destination row and square.
   * @param row The destination row.
   * @param column The destination column.
   * @return A reference to this @c PieceMove.
   * @throw Never throws.
   */
  PieceMove& setGoTo(dim_type row, dim_type column) noexcept;

  /**
   * @brief Determine if it is check mate.
   * @return True if the move results in a captured king.
   * @throw Never throws.
   */
  bool isMate() const noexcept;

private:
  /**
   * Represents the piece tha is making the move.
   */
  Square mFrom;

  /**
   * @brief Represents the location where the piece is moving to.
   * @detail If there is a capture, then the only time when <em>mPromo</em>
   *  and <em>mCapture</em> will not overlap is when a pawn is captured by
   *  <em>en passant</em>. If there is a pawn promotion, then <em>mPromo</em>
   *  will hold the information for the promoted piece.
   */
  Square mPromo;

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

} // namespace zoor

#endif // _PIECEMOVES_H
