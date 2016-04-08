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

std::vector<Board> readFEN(const char *fileName);
std::vector<Board> readFEN(const std::string &fileName);

void writeFEN(const char *fileName, const Board &board);
void writeFEN(const char *fileName, const std::vector<Board> &board);
void writeFEN(const std::string &fileName, const Board &board);
void writeFEN(const std::string &fileName, const std::vector<Board> &board);

}

#endif // _NOTATION_H
