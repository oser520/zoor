/**
 * @file notation.cc
 * @author Omar A Serrano
 * @date 2016-04-09
 */
#include <string>
#include <sstream>
#include <vector>
#include <ifstream>
#include <utility>

#include "notation.hh"
#include "piececode.hh"
#include "square.hh"
#include "board.hh"
#include "chesserror.hh"

// using from STL
using std::vector;
using std::string;
using std::istringstream;
using std::sort;
using std::unique;

// using from zoor
using Board::dim_type;

namespace zoor {

namespace {

// @brief Read the contents of one single rank from the first field in a FEN record.
// @details The assumptions are listed here:
// @li Does not contain more than 8 characters.
// @li Valid digits are 1 to 8, but if there are multiple digits their sum cannot
// exceed 8.
// @li The only valid letters are those that represent white or black pieces.
// @param rankLine The string representing one rank.
// @param squareList A reference to a vector of squares where squares are added.
// @param row The number of row representing the current rank.
// @return The total number of pieces found in the rank.
// @throw ChessError if the rankLine violates any of the assumptions.
//
size_t
readRank(string &rankLine, vector<Square>& squareList, dim_type row);

// @brief Reads the color of the player who moves next.
// @details The assumptions are:
// @li Contains exactly one character.
// @li Valid characters are <em>w</em> and <em>b</em>.
// @param colorLine The string representing the color.
// @return The @c PieceColor for black or white.
// @throw ChessError if the rankLine violates any of the assumptions.
//
PieceColor
readColor(const string &colorLine);

// @brief Read the castling rights from the 3rd field in a FEN record.
// @details The assumptions are:
// @li Does not contain more than 4 characters.
// @li Legal characters are -, K, Q, k, and q.
// @li If - is present, then this should be the only character available.
// @li Valid characters should not repeat.
// @param infoLine The string representing the castling rights.
// @return A @c BoardInfo representing the castling rights.
// @throw ChessError if the infoLine violates any of the assumptions.
//
BoardInfo
readBoardInfo(string &infoLine);

// @brief Read en passant info from the 4th field in a FEN record.
// @details The assumptions are:
// @li Does not contain more than 2 characters.
// @li Legal characters are -, a-h, 3, and 6.
// @li If - is present, then the field should not contain more chars.
// @li If - is not present, then the field should contain 2 chars, the first should
// be a letter in a-h, and second should be 3 or 6.
// @details If there is an en passant, then the caller of this function should
// enforce that there is a pawn that makes this info true.
// @param field The string representing the 4th field in the FEN record.
// @return A @c PieceMove representing the last move.
// @throw ChessError if the field violates any of the assumptions.
//
PieceMove
readEnPassant(const string &field);

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

namespace { // private function definitions

// @copydoc readRank(const string&,vector<Square>&,dim_type)
//
size_t
readRank(const string &rankLine, vector<Square> &squareList, dim_type row)
{
  // check rank line is not empty and does not exceed max chars
  if (rankLine.empty() || rankLine.size() > FenSymbols::RANK_LENGTH)
    throw ChessError("FEN record is not valid");

  // check that we only have valid chars
  if (rankLine.find_first_not_of(FenSymbols::RANK_CHR) != string::npos)
    throw ChessError("FEN record is not valid");

  dim_type col = 0;
  size_t numPieces = 0;

  for (auto &c : rankLine) {
    // check for empty squares
    if (c >= '1' && c <= '8') {
      col += c - '0';
      continue;
    }

    // convert code to piece
    auto code = fenPiece(c);
    squareList.emplace_back(row, col, code);
    ++col;
    ++numPieces;
  }

  // check that number of empty squares doesn't exceed length of row
  if (col > FenSymbols::RANK_LENGTH)
    throw ChessError("FEN record is not valid");

  return numPieces;
}

// @copydoc readColor(const string&)
//
PieceColor
readColor(const string &colorLine)
{
  if (colorLine.size() != 1)
    throw ChessError("FEN record is not valid");

  if (colorLine.find_first_not_of(FenSymbols::VALID_COLOR) != string::npos)
    throw ChessError("FEN record is not valid");

  return colorLine.front() == 'w' ? PieceColor::WHITE : PieceColor::BLACK;
}

// @copydoc readBoardInfo(string&)
//
BoardInfo
readBoardInfo(string &infoLine)
{
  // check info line is not empty and does not exceed max chars
  if (infoLine.empty() || infoLine.size() > FenSymbols::CASTLE_LENGTH)
    throw ChessError("FEN record is not valid");

  if (infoLine.size() == 1) {
    // if only one char, then it should be dash
    if (infoLine[0] != FenSymbols::DASH)
      throw ChessError("FEN record is not valid");

    // remove castling rights
    BoardInfo info;
    info.rookA1On();
    info.rookH1On();
    info.rookA8On();
    info.rookH8On();

    return info;
  }

  // check that we only have valid chars
  if (infoLine.find_first_not_of(FenSymbols::CASTLE_CHR) != string::npos)
    throw ChessError("FEN record is not valid");

  // check that we only have unique values
  auto itend = infoLine.end();
  sort(infoLine.begin(), itend);
  if (unique(infoLine.begin(), itend) != itend)
    throw ChessError("FEN record is not valid");

  // assume no castling rights
  bool wCastle = false;
  bool wCastleLong = false;
  bool bCastle = false;
  bool bCastleLong = false;

  // process castling rights
  for (auto &c : infoLine) {
    switch (c) {
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
      // should never get here
      throw ChessError("FEN record is not valid");
    }
  }

  BoardInfo info;

  // remove short castling for white
  if (!wCastle)
    info.rookH1On();

  // remove long castling for white
  if (!wCastleLong)
    info.rookA1On();

  // remove short castling for black
  if (!bCastle)
    info.rookH1On();

  // remove long castling for black
  if (!bCastleLong)
    info.rookA1On();

  return info;
}

} // anonymous namespace

} // zoor
