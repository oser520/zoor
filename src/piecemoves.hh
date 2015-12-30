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
  friend std::ostream& operator<<(std::ostream &os, const PieceMoves &pm) noexcept;
  friend bool operator==(const PieceMoves &pm1, const PieceMoves &pm2) noexcept;

public:
  // typedefs
  using iterator = std::vector<MoveTo>::iterator;
  using const_iterator = std::vector<MoveTo>::const_iterator;
  
  // copy control
  PieceMoves();
  PieceMoves(const PieceMoves &pm);
  PieceMoves(PieceMoves &&pm);
  PieceMoves& operator=(const PieceMoves &pm);
  PieceMoves& operator=(PieceMoves &&pm);
  ~PieceMoves() noexcept;
  
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

