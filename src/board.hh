/**
 * @file board.hh
 * @author Omar A Serrano
 * @date 2015-12-18
 */

#ifndef _BOARD_H
#define _BOARD_H

namespace zoor {

/* TODO:
 * - create piece representation based on 4 bits
 * - determine how to represent board (e.g. use dynamic memory?) 
 * - provide member variables to maintain information, including
 *   - 50 move tie
 *   - 3 move tie
 *   - number of moves in game so far
 *   - black/whites turn
 *   - number of pieces
 * - provide member functions
 *   - get next move
 *   - serialize board
 *   - get position value
 *   - info about position
 *   - is mate
 */

class Board {
public:
	/* copy control */
	Board() = default;
	Board(const Board &board) = default;
	Board(Board &&board) = default;
	Board& operator=(const Board &board) = default;
	Board& operator=(Board &&board) = default;
	~Board() = default;
};

} // namespace zoor

#endif 
