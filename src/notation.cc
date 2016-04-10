/**
 * @file notation.cc
 * @author Omar A Serrano
 * @date 2016-04-09
 */

#include <string>
#include <vector>
#include <ifstream>
#include <utility>

#include "notation.hh"
#include "board.hh"
#include "chesserror.hh"

namespace zoor {

// readFEN with param std::ifstream.
// TODO: optionally add logging information, such as how many boards are processed
// and if there are any errors.
std::vector<Board> readFEN(std::ifstream &inFile)
{
  std::string line;
  std::vector<Board> boardList;

  while (std::getline(inFile, line)) {
    if (line.empty()) continue;
    auto board = readFEN(line);
    boardList.emplace_back(std::move(board));
  }

  if (inFile.fail() && !inFile.eof())
    throw ChessError("Error processing FEN file");

  return boardList;
}

} // zoor
