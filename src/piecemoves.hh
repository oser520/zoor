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
};

} // namespace zoor

#endif // _PIECEMOVES_H

