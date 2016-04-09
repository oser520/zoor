/**
 * @file notation.hh
 * @author Omar A Serrano
 * @date 2016-04-07
 */
#ifndef _NOTATION_H
#define _NOTATION_H

#include <string>
#include <vector>

#include "board.hh"

namespace zoor {

/**
 * @brief Read a chess position FEN notation from a file.
 * @param fileName The name of the file.
 * @return A vector of @c Boards, which may contain 0 or more boards.
 */
std::vector<Board> readFEN(const char *fileName);

/**
 * @copydoc readFEN(const char*)
 */
std::vector<Board> readFEN(const std::string &fileName);

/**
 * @brief Write a board to a file in FEN notation.
 * @param fileName The name of the file.
 * @param board The @c Board to be written.
 */
void writeFEN(const char *fileName, const Board &board);

/**
 * @brief Write a board to a file in FEN notation.
 * @param fileName The name of the file.
 * @param boardList A vector of boards, each of which gets one line.
 */
void writeFEN(const char *fileName, const std::vector<Board> &boardList);

/**
 * @copydoc writeFen(const char*,const &)
 */
void writeFEN(const std::string &fileName, const Board &board);

/**
 * @copydoc writeFen(const char*,const std::vector<Board>&)
 */
void writeFEN(const std::string &fileName, const std::vector<Board> &boardList);

}

#endif // _NOTATION_H
