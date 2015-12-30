/**
 * @file piecemoves.hh
 * @author Omar A Serrano
 * @date 2015-12-29
 */
#ifndef _PIECEMOVES_H
#define _PIECEMOVES_H

namespace zoor {

/**
 * Represents a position in the baord.
 */
struct Square
{
  unsigned short mRow;
  unsigned short mCol;
};

/**
 * @brief Represents a list of moves for a given piece from a particular position in
 * the board.
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
  
  // copy control
  PieceMoves();
  PieceMoves(const PieceMoves&);
  PieceMoves(PieceColor, PieceCode, Square);
  PieceMoves(PieceColor, PieceCode, Square, std::vector<MoveTo>);
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
  
private:
  PieceColor mColor;
  PieceCode mPiece;
  Square mSquare;
  std::vector<MoveTo> mMoves;

public:
  /**
   * A move to a given position.
   */
  struct MoveTo
  {
    PieceColor mColor;
    PieceCode mPiece;
    Square mSquare;
  };
};

} // namespace zoor

#endif // _PIECEMOVES_H

