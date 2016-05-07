/////////////////////////////////////////////////////////////////////////////////////
/// @file piecemove.hh
/// @author Omar A Serrano
/// @date 2015-12-29
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _PIECEMOVES_H
#define _PIECEMOVES_H

//
// STL
//
#include <functional>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "square.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// declarations
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief Maintains information about a move, including the destination square, if
/// there's a capture, and if there's a promotion, .i.e., the pawn moves to the last
/// row and becomes a more powerful piece.
///
class PieceMove
{
public:
  ///
  /// @brief Constructor with info for piece that is moving.
  /// @param row The row of the piece that is moving.
  /// @param column The column of the piece that is moving.
  /// @param piece The piece that is moving.
  /// @param color The color of the piece that is moving.
  /// @throw Never throws.
  ///
  PieceMove(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @brief Constructor with info for piece that is moving.
  /// @param row The row of the piece that is moving.
  /// @param column The column of the piece that is moving.
  /// @param code The bit pattern containing the piece and color info.
  /// @throw Never throws.
  ///
  PieceMove(dim_t row, dim_t column, piece_t code) noexcept;

  ///
  /// @brief Constructor with info for piece that is moving, and where it is moving.
  /// @param fromRow The row from where the piece is moving.
  /// @param fromColumn The column from where the piece is moving.
  /// @param code The bit pattern containing the piece and color info.
  /// @param toRow The row where the piece is moving.
  /// @param toColumn The column where the piece is moving.
  /// @throw Never throws.
  ///
  PieceMove
    (dim_t fromRow,
     dim_t fromColumn,
     piece_t code,
     dim_t toRow,
     dim_t toColumn) noexcept;

  ///
  /// @brief Default constructor.
  /// @throw Never throws.
  ///
  PieceMove() noexcept;

  ///
  /// @brief Default copy constructor.
  /// @param pieceMove The @c PieceMove being copied.
  /// @throw Never throws.
  ///
  PieceMove(const PieceMove &pieceMove) noexcept = default;

  ///
  /// @brief Default move constructor.
  /// @param pieceMove The @c PieceMove being moved.
  /// @throw Never throws.
  ///
  PieceMove(PieceMove &&pieceMove) noexcept = default;

  ///
  /// @brief Default copy assignment.
  /// @param pieceMove The @c PieceMove being copied.
  /// @throw Never throws.
  ///
  PieceMove&
  operator=(const PieceMove &pieceMove) noexcept = default;

  ///
  /// @brief Default move assignment.
  /// @param pieceMove The @c PieceMove being moved.
  /// @throw Never throws.
  ///
  PieceMove&
  operator=(PieceMove &&pieceMove) noexcept = default;

  ///
  /// @brief Default destructor.
  /// @throw Never throws.
  ///
  ~PieceMove() noexcept = default;

  ///
  /// @return The piece.
  /// @throw Never throws.
  ///
  piece_t
  code() const noexcept;

  ///
  /// @brief Set the piece making the move.
  /// @brief piece The piece making the move.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  code(piece_t piece) noexcept;

  ///
  /// @return The piece making the move.
  /// @throw Never throws.
  ///
  Piece
  piece() const noexcept;

  ///
  /// @brief Set the piece making the move.
  /// @brief piece The piece making the move.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  piece(Piece piece) noexcept;

  ///
  /// @brief Sets the color and piece for the piece that is moving.
  /// @param piece The piece that is moving.
  /// @param color The color of the piece that is moving.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  piece(Piece piece, Color color) noexcept;

  ///
  /// @brief Sets the information for the piece that is moving.
  /// @param row The row location of the piece.
  /// @param column The column location of the piece.
  /// @param code The bit pattern with color and piece info.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  piece(dim_t row, dim_t column, piece_t code) noexcept;

  ///
  /// @brief Sets the information for the piece that is moving.
  /// @param row The row location of the piece.
  /// @param column The column location of the piece.
  /// @param piece The piece.
  /// @param color The color of the piece.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  piece(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @return The color of the piece making the move.
  /// @throw Never throws.
  ///
  Color
  color() const noexcept;

  ///
  /// @brief Set the color of the piece making the move.
  /// @param color The color of the piece making the move.
  /// @return A reference to this PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  color(Color color) noexcept;

  ///
  /// @return The row of the piece making the move.
  /// @throw Never throws.
  ///
  dim_t
  row() const noexcept;

  ///
  /// @brief Set the row of the piece making the move.
  /// @param row The row of the piece making the move.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  row(dim_t row) noexcept;

  ///
  /// @return The column of the piece making the move.
  /// @throw Never throws.
  ///
  dim_t
  column() const noexcept;

  ///
  /// @brief Set the column of the piece making the move.
  /// @param column The column of the piece making the move.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  column(dim_t column) noexcept;

  ///
  /// @return The row and column of the piece makin the move.
  /// @throw Never throws.
  ///
  std::pair<dim_t, dim_t>
  location() const noexcept;

  ///
  /// @brief Set the row and column of the piece making the move.
  /// @param row The row of the piece making the move.
  /// @param column The column of the piece making the move.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  location(dim_t row, dim_t column) noexcept;

  ///
  /// @return A reference to @c Square making the move.
  /// @throw Never throws.
  ///
  const Square&
  square() const noexcept;

  ///
  /// @brief Get the piece of the square where the piece is moving to.
  /// @details The piece at the destination square is only different from the piece
  /// at the source square when move results in pawn promotion.
  /// @return The piece.
  /// @throw Never throws.
  ///
  piece_t
  toCode() const noexcept;

  ///
  /// @brief Set the piece at the destination square.
  /// @details The piece at the destination square is only different from the piece
  /// at the source square when move results in pawn promotion.
  /// @brief piece The piece at the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toCode(piece_t piece) noexcept;

  ///
  /// @return The piece at the destination square.
  /// @throw Never throws.
  ///
  Piece
  toPiece() const noexcept;

  ///
  /// @brief Set the piece at the destination square.
  /// @param piece The piece at the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toPiece(Piece piece) noexcept;

  ///
  /// @brief Set the piece at the destination square.
  /// @param piece The piece at the destination square.
  /// @param color The color at the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toPiece(Piece piece, Color color) noexcept;

  ///
  /// @brief Set the piece at the destination square.
  /// @param row The row of destination square.
  /// @param column The column of destination square.
  /// @param piecd The piece at the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toPiece(dim_t row, dim_t column, piece_t piece) noexcept;

  ///
  /// @brief Set the piece at the destination square.
  /// @param row The row of destination square.
  /// @param column The column of destination square.
  /// @param piecd The piece at the destination square.
  /// @param color The color at the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toPiece(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @return The color of the destination piece.
  /// @throw Never throws.
  ///
  Color
  toColor() const noexcept;

  ///
  /// @brief Set the color of the destination piece.
  /// @param color The color of the destination piece.
  /// @return A reference to this PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toColor(Color color) noexcept;

  ///
  /// @return The row of the destination square.
  /// @throw Never throws.
  ///
  dim_t
  toRow() const noexcept;

  ///
  /// @brief Set the row of the destination square.
  /// @param row The row of the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toRow(dim_t row) noexcept;

  ///
  /// @return The column of the destination square.
  /// @throw Never throws.
  ///
  dim_t
  toColumn() const noexcept;

  ///
  /// @brief Set the column of the destination square.
  /// @param column The column of the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toColumn(dim_t column) noexcept;

  ///
  /// @return The row and column of the destination square.
  /// @throw Never throws.
  ///
  std::pair<dim_t, dim_t>
  toLocation() const noexcept;

  ///
  /// @brief Set the row and column of the destination square.
  /// @param row The row of the destination square.
  /// @param column The column of the destination square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  toLocation(dim_t row, dim_t column) noexcept;

  ///
  /// @return A reference to the destintion square.
  /// @throw Never throws.
  ///
  const Square&
  toSquare() const noexcept;

  ///
  /// @brief Get the piece of the other square.
  /// @details The other square may contain capture piece if the move results in a
  /// capture, or a rook of the same color if the move represents castling.
  /// @return The piece.
  /// @throw Never throws.
  ///
  piece_t
  otherCode() const noexcept;

  ///
  /// @brief Set the other piece.
  /// @details The other square may contain a capture piece if the move results in a
  /// capture, or a rook of the same color if the move represents castling.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherCode(piece_t piece) noexcept;

  ///
  /// @return The piece at the other square.
  /// @throw Never throws.
  ///
  Piece
  otherPiece() const noexcept;

  ///
  /// @brief Set the piece at the other square.
  /// @param piece The piece at the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherPiece(Piece piece) noexcept;

  ///
  /// @brief Set the piece at the other square.
  /// @param piece The piece at the other square.
  /// @param color The color at the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherPiece(Piece piece, Color color) noexcept;

  ///
  /// @brief Set the piece at the other square.
  /// @param row The row of other square.
  /// @param column The column of other square.
  /// @param piecd The piece at the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherPiece(dim_t row, dim_t column, piece_t piece) noexcept;

  ///
  /// @brief Set the piece at the other square.
  /// @param row The row of other square.
  /// @param column The column of other square.
  /// @param piecd The piece at the other square.
  /// @param color The color at the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherPiece(dim_t row, dim_t column, Piece piece, Color color) noexcept;

  ///
  /// @return The color of the other piece.
  /// @throw Never throws.
  ///
  Color
  otherColor() const noexcept;

  ///
  /// @brief Set the color of the other piece.
  /// @param color The color of the other piece.
  /// @return A reference to this PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherColor(Color color) noexcept;

  ///
  /// @return The row of the other square.
  /// @throw Never throws.
  ///
  dim_t
  otherRow() const noexcept;

  ///
  /// @brief Set the row of the other square.
  /// @param row The row of the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherRow(dim_t row) noexcept;

  ///
  /// @return The column of the other square.
  /// @throw Never throws.
  ///
  dim_t
  otherColumn() const noexcept;

  ///
  /// @brief Set the column of the other square.
  /// @param column The column of the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherColumn(dim_t column) noexcept;

  ///
  /// @return The row and column of the other square.
  /// @throw Never throws.
  ///
  std::pair<dim_t, dim_t>
  otherLocation() const noexcept;

  ///
  /// @brief Set the row and column of the other square.
  /// @param row The row of the other square.
  /// @param column The column of the other square.
  /// @return A reference to this @c PieceMove.
  /// @throw Never throws.
  ///
  PieceMove&
  otherLocation(dim_t row, dim_t column) noexcept;

  ///
  /// @return A reference to the other square.
  /// @throw Never throws.
  ///
  const Square&
  otherSquare() const noexcept;

  ///
  /// @brief Determine if the move has resulted in a capture.
  /// @return True if the move has a capture, false otherwise.
  /// @throw Never throws.
  ///
  bool
  isCapture() const noexcept;

  ///
  /// @brief Determine if the move has resulted in a promotion.
  /// @return True if the move has a promotion, false otherwise.
  /// @throw Never throws.
  ///
  bool
  isPromo() const noexcept;

  ///
  /// @return True if the move results in a captured king.
  /// @throw Never throws.
  ///
  bool
  isMate() const noexcept;

  ///
  /// @return True if the move represents short castling.
  /// @throw Never throws.
  ///
  bool
  isCastle() const noexcept;

  ///
  /// @return True if the move represents long castling.
  /// @throw Never throws.
  ///
  bool
  isCastleLong() const noexcept;

  ///
  /// @return True if the move represents en passant.
  /// @throw Never throws.
  ///
  bool
  isEnPassant() const noexcept;

  ///
  /// @return A string representing the @c PiecMove.
  ///
  std::string
  toString() const;

  ///
  /// @return The numeric hash code for this @c PieceMove.
  /// @throw Never throws.
  ///
  size_t
  hashCode() const noexcept;

private:
  // Square piece is moving from.
  Square mFrom;

  // Square piece is moving to.
  Square mTo;

  // The captured piece, or rook on a castling move.
  Square mOther;
};

///
/// @brief Equality operator for @c PieceMove.
/// @param pm1 The first @c PieceMove.
/// @param pm2 The second @c PieceMove.
/// @return True if the moves are equal, false otherwise.
/// @throw Never throws.
///
bool
operator==(const PieceMove &pm1, const PieceMove &pm2) noexcept;

///
/// @brief Non-equality operator for @c PieceMove.
/// @param pm1 The first @c PieceMove.
/// @param pm2 The second @c PieceMove.
/// @return True if the moves are not equal, false otherwise.
/// @throw Never throws.
///
bool
operator!=(const PieceMove &pm1, const PieceMove &pm2) noexcept;

///
/// @brief Output operator for @c PieceMove.
/// @param os A reference to the output stream.
/// @param pm The @c PieceMove.
/// @return A reference to the output stream.
///
std::ostream&
operator<<(std::ostream &os, const PieceMove &pm);

/////////////////////////////////////////////////////////////////////////////////////
// definitions
/////////////////////////////////////////////////////////////////////////////////////

//
// from row getter
//
inline PieceMove::dim_type
PieceMove::fromRow() const noexcept
{
  return mFrom.row();
}

//
// from column getter
//
inline PieceMove::dim_type
PieceMove::fromColumn() const noexcept
{
  return mFrom.column();
}

//
// the row getter for the destination row
//
inline PieceMove::dim_type
PieceMove::toRow() const noexcept
{
  return mPromo.row();
}

//
// the column getter for the destination column
//
inline PieceMove::dim_type
PieceMove::toColumn() const noexcept
{
  return mPromo.column();
}

//
// the row getter for the captured piece
//
inline PieceMove::dim_type
PieceMove::captureRow() const noexcept
{
  return mCapture.row();
}

//
// the column getter for the captured piece
//
inline PieceMove::dim_type
PieceMove::captureColumn() const noexcept
{
  return mCapture.column();
}

//
// source square getter
//
inline Square
PieceMove::fromSquare() const noexcept
{
  return mFrom;
}

//
// source piece getter
//
inline PieceCode
PieceMove::fromPiece() const noexcept
{
  return mFrom.piece();
}

//
// source piece color getter
//
inline PieceColor
PieceMove::fromColor() const noexcept
{
  return mFrom.color();
}

//
// get the captured square
//
inline Square
PieceMove::captureSquare() const noexcept
{
  return mCapture;
}

//
// get the captured piece
//
inline PieceCode
PieceMove::capturePiece() const noexcept
{
  return mCapture.piece();
}

//
// get the captured piece's color
//
inline PieceColor
PieceMove::captureColor() const noexcept
{
  return mCapture.color();
}

//
// does move result in promotion
//
inline bool
PieceMove::isPromo() const noexcept
{
  return mPromo.piece() != PieceCode::NONE;
}

//
// promotion square
//
inline Square
PieceMove::promoSquare() const noexcept
{
  return mPromo;
}

//
// promotion piece getter
//
inline PieceCode
PieceMove::promoPiece() const noexcept
{
  return mPromo.piece();
}

//
// promotion piece color getter
//
inline PieceColor
PieceMove::promoColor() const noexcept
{
  return mPromo.color();
}

//
// check if the move results in mate
//
inline bool
PieceMove::isMate() const noexcept
{
  return isKing(mCapture.piece());
}

//
// check if the move represents short castling
//
inline bool
PieceMove::isCastle() const noexcept
{
  return mCastleInfo == 0x1;
}

//
// check if the move represents long castling
//
inline bool
PieceMove::isCastleLong() const noexcept
{
  return mCastleInfo == 0x2;
}

//
// are moves different
//
inline bool
operator!=(const PieceMove &pm1, const PieceMove &pm2) noexcept
{
  return !(pm1 == pm2);
}

} // namespace zoor

namespace std {

///
/// @brief PieceMove specialization for <em>hash</em>. Needs to be defined within
/// std namespece.
///
template<>
struct hash<zoor::PieceMove>
{
  using argument_type = zoor::PieceMove;
  using result_type = size_t;

  result_type
  operator()(const argument_type& arg)
  {
    return arg.hashCode();
  }
};

} // std
#endif // _PIECEMOVES_H
