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

/**
 * @brief Move the knight at the given row and column.
 * @param row The row where the knight is located.
 * @param column The column where the knight is located.
 * @param board The board where the pawn will move.
 * @return A vector of squares where the knight can move.
 * @throw Never throws.
 */
vector<PieceMove>
moveKnight(dim_type row, dim_type column, const Board &board) noexcept;

/**
 * @brief Move the bishop at the given row and column.
 * @param row The row where the bishop is located.
 * @param column The column where the bishop is located.
 * @param board The board where the pawn will move.
 * @return A vector of squares where the bishop can move.
 * @throw Never throws.
 */
vector<PieceMove>
moveBishop(dim_type row, dim_type column, const Board &board) const noexcept;

} // namespace zoor
