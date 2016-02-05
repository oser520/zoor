/**
 * @file moves.hh
 * @author Omar A Serrano
 * @date 2016-02-03
 */

// stl headers
#include <vector>

// zoor headers
#include "piececode.hh"
#include "piecemoves.hh"
#include "board.hh"

namespace zoor {

/**
 * @brief Move the pawn at the given row and column.
 * @param row The row where the pawn is located.
 * @param column The column where the pawn is located.
 * @param board The board where the pawn will move.
 * @return A vector of moves.
 * @throw Never throws.
 */
vector<PieceMove>
movePawn(dim_type row, dim_type column, const Board &board) noexcept;
} // namespace zoor
