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
#include <algorithm>

#include "notation.hh"
#include "piececode.hh"
#include "square.hh"
#include "board.hh"
#include "chesserror.hh"

// TODO: Declare and define fenPiece.
// fenPiece will convert a valid char to a piececode_t.

// TODO: Add const static members to FenSymbols.
// These static members contain valid fen symbols, such as valid chars for a rank.

// TODO: Move assumptions comments to location of function defintion.

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

/// @brief Read the contents of one single rank from the first field in a FEN record.
/// @details The assumptions are listed here:
/// @li Does not contain more than 8 characters.
/// @li Valid digits are 1 to 8, but if there are multiple digits their sum cannot
/// exceed 8.
/// @li The only valid letters are those that represent white or black pieces.
/// @param rankLine The string representing one rank.
/// @param squareList A reference to a vector of squares where squares are added.
/// @param row The number of row representing the current rank.
/// @return The total number of pieces found in the rank.
/// @throw ChessError if the rankLine violates any of the assumptions.
size_t
readRank(const string &rankLine, vector<Square>& squareList, const dim_type row);

/// @brief Reads the color of the player who moves next.
/// @details The assumptions are:
/// @li Contains exactly one character.
/// @li Valid characters are <em>w</em> and <em>b</em>.
/// @param colorLine The string representing the color.
/// @return The @c PieceColor for black or white.
/// @throw ChessError if the rankLine violates any of the assumptions.
PieceColor
readColor(const string &colorLine);

/// @brief Read the castling rights from the 3rd field in a FEN record.
/// @details The assumptions are:
/// @li Does not contain more than 4 characters.
/// @li Legal characters are -, K, Q, k, and q.
/// @li If - is present, then this should be the only character available.
/// @li Valid characters should not repeat.
/// @param infoLine The string representing the castling rights. Should not be marked
/// as const, because it is sorted in order to find unique values in string.
/// @return A @c BoardInfo representing the castling rights.
/// @throw ChessError if the infoLine violates any of the assumptions.
BoardInfo
readBoardInfo(string &infoLine);

/// @brief Read en passant info from the 4th field in a FEN record.
/// @details The assumptions are:
/// @li Does not contain more than 2 characters.
/// @li Legal characters are -, a-h, 3, and 6.
/// @li If - is present, then the field should not contain more chars.
/// @li If - is not present, then the field should contain 2 chars, the first should
/// be a letter in a-h, and second should be 3 or 6.
/// @details If there is an en passant, then the caller of this function should
/// enforce that there is a pawn that makes this info true.
/// @param field The string representing the 4th field in the FEN record.
/// @return A @c PieceMove representing the last move.
/// @throw ChessError if the field violates any of the assumptions.
PieceMove
readEnPassant(const string &field);

} // anonymous namespace

// readFEN with param std::ifstream.
// TODO: this is a good place to add logging info
std::vector<Board>
readFEN(std::ifstream &inFile)
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
// TODO: implement
Board
readFEN(std::string &fenLine)
{
  string buff;
  int numRank = 7, numPiece = 0;
  vector<Square> squareList;
  istringstream iss(fenLine);

  // process the last ranks, 8 through 2
  for (; numRank > 0; --numRank) {
    if (!getline(iss, buff, "/"))
      throw ChessError("FEN record is not valid");

    numPiece += readRank(buff, squareList, numRank);
  }

  // process the 1st rank
  if (!(iss >> buff))
    throw ChessError("FEN record is not valid");

  numPiece += readRank(buff, squareList, numRank);

  // check that we don't have more than 32 pieces
  if (numPieces > 32)
    throw ChessError("FEN record is not valid");

  // TODO: check that we have only two kings, one each for blak and white
  // TODO: check that we don't have more than 16 pawns
  // TODO: check that we don't have more than 10 pieces of bishop, rook, knight
  // TODO: check that we don't have more than 9 queens

  // process color to move next
  if (!(iss >> buff))
    throw ChessError("FEN record is not valid");

  auto color = readColor(buff);

  // process board info
  if (!(iss >> buff))
    throw ChessError("FEN record is not valid");

  auto info = readBoardInfo(buff);

  // process en passant
  if (!(iss >> buff))
    throw ChessError("FEN record is not valid");

  auto pieceMove = readEnPassant(buff);

  // process half moves
  size_t halfMoves;
  if (!(iss >> halfMoves))
    throw ChessError("FEN record is not valid");

  // process full moves
  size_t fullMoves;
  if (!(iss >> fullMoves))
    throw ChessError("FEN record is not valid");

  // TODO: create class object to hold the board and the move counts

  return Board();
}

namespace { // private function definitions

// readRank enforces the assumptions about rankLine by looking at some fields in
// FenSymbols: RANK_LENGTH and RANK_CHR. RANK_LENGTH represents the maximum number
// of characters that that a row may contain, and RANK_CHR represents the valid
// characters that a FEN row may contain. Empty squares are marked with digits,
// but a row may not contain more than 8 empty squares, and this is enforced by
// summing the number of empty squares found in a row.
size_t
readRank(const string &rankLine, vector<Square> &squareList, const dim_type row)
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

// @copydoc readEnPassant(const string&)
//
PieceMove
readEnPassant(const string &field)
{
  // field cannot be empty or exceed two chars
  if (field.empty() || field.size() > 2)
    throw ChessError("FEN record is not valid");

  if (field.size() == 1) {
    // if only one char, it needs to be dash
    if (field.front() != FenSymbols::DASH)
      throw ChessError("FEN record is not valid");

    return PieceMove();
  }

  // check column letter is valid
  auto colChr = field.front();
  if (colChr < 'a' || colChr > 'h')
    throw ChessError("FEN record is not valid");

  // set the column number
  dim_type col = colChr - 'a';

  // check row number is valid
  auto rowChr = field.back();
  if (rowChr != '3' && rowChr != '6')
    throw ChessError("FEN record is not valid");

  // set the row numbers and the piece code
  piececode_t code;
  dim_type fromRow, toRow;

  if (rowChr == '3') {
    fromRow = 1;
    toRow = 3;
    code = PieceColor::WHITE | PieceCode::PAWN;
  } else {
    fromRow = 6;
    toRow = 4;
    code = PieceColor::BLACK | PieceCode::PAWN;
  }

  return PieceMove(fromRow, col, code, toRow, col);
}

} // anonymous namespace

} // zoor
