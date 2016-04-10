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
#include "piececode.hh"
#include "square.hh"
#include "board.hh"
#include "chesserror.hh"

namespace zoor {

namespace {

// @brief Read the contents of one single rank from the first field in a FEN record.
// @details The assumptions are listed here:
// @li Does not contain more than 8 characters.
// @li Valid digits are 1 to 8, but if there are multiple digits their sum cannot
// exceed 8.
// @li The only valid letters are those that represent white or black pieces.
// @param fenLine The string representing the one rank.
// @return A vector of squares where pieces are located.
//
std::vector<Square>
readRank(std::string &fenLine);

} // anonymous namespace

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

// readFEN with param std::string.
Board readFEN(std::string &fenLine)
{
  FenSymbols fen;
  auto it = fenLine.begin();
  auto itend = fenLine.end();

  // ignore leading spaces
  while (it != itend && *it == fen.space)
    ++it;

  // if nothing else in FEN record, then error
  if (it == itend)
    throw ChessError("FEN record is empty");

  size_t idx;
  int row = 7, col = 0, tok = 0;
  std::vector<Square> squareList;

  while (it != itend) {
    // done if find space
    if (*it == fen.space) {
      ++it;
      break;
    }

    if (*it == fen.slash) {
      // proceed to next row if slash found
      --row;

      // check that we don't process more than 8 rows
      if (row < 0)
        throw ChessError("FEN record is not valid");

      col = 0;
      tok = 0;
    } else if (*it > '0' && *it < '9') {
      // increment column count by number of empty squares
      col += *it - '0';
    } else if ((idx = fen.wPiece.find(*it)) && idx != string::npos) {
      // found white piece
      auto code = fenPiece(*it);
      squareList.emplace_back(row, col, code);
      ++col;
    } else if ((idx = fen.bPiece.find(*it)) && idx != string::npos) {
      // found black piece
      auto code = fenPiece(*it);
      squareList.emplace_back(row, col, code);
      ++col;
    } else {
      // char not recognized
      throw ChessError("FEN record is not valid");
    }

    ++it;
    ++tok;

    // check that we don't process more than 8 tokens per row
    if (tok > 8)
      throw ChessError("FEN record not valid");
  }

  // if nothing else in FEN record, then error
  if (it == itend)
    throw ChessError("FEN record is not valid");

  // set the next color to move
  PieceColor color;
  if (*it == fen.cWhite)
    color = PieceColor::WHITE;
  else if (*it == fen.cBlack)
    color = PieceColor::BLACK;
  else
    throw ChessError("FEN record is not valid");

  if (++it == itend)
    throw ChessError("FEN record is not valid");

  tok = 0;
  bool wCastle = false;
  bool wCastleLong = false;
  bool bCastle = false;
  bool bCastleLong = false;
  bool foundDash = false;

  while (it != itend) {
    // zero castling rights
    if (*it == fen.space) {
      ++it;
      break;
    }

    // shouldn't get here after finding dash
    if (foundDash)
      throw ChessError("FEN record is not valid");

    switch (*it) {
    case '-':
      foundDash = true;
      break;
    case 'K':
      wCastle = true;
      break;
    case 'Q':
      wCastleLong = true;
      break;
    case 'k':
      bCastle = true;
      break;
    case 'q':
      bCastleLong = true;
      break;
    default:
      // shouldn't get here
      throw ChessError("FEN record is not valid");
    }

    ++it;
    ++tok;

    // castling rights are encoded in 4 chars max
    if (tok > 4)
      throw ChessError("FEN record is not valid");
  }

  // TODO: handle setting BoardInfo here.

  if (it == itend)
    throw ChessError("FEN record is not valid");

  row = -1;
  col = -1;
  foundDash = false;
  tok = 0;

  while (it != itend) {
    if (it == fen.space) {
      ++it;
      break;
    }

    // shouldn't get here if found dash already
    if (foundDash)

    if (*it == '-') {
      foundDash = true;
    } else if (*it >= 'a' && *it <= 'h') {
      col = *it - 'a';
    } else if (*it >= '1' && *it <= '8') {
      row = *it - '1';
    } else
      throw ChessError("FEN record is not valid");

    ++it;
    ++tok;

    // en passant encoded in 2 chars max
    if (tok > 2)
      throw ChessError("FEN record is not valid");
  }

  if (!foundDash) {
    if (row < 0 || col < 0)
      throw ChessError("FEN record is not valid");
    // TODO: handle setting the en passant (i.e. last move)
  }

  // TODO: add logic to parse the half move clock
  // TODO: add logic to parse the full move number

  return Board();
}

} // zoor
