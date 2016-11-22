////////////////////////////////////////////////////////////////////////////////
//! @file iofen.cc
//! @author Omar A Serrano
//! @date 2016-04-09
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "chesserror.hh"
#include "fenrecord.hh"
#include "iofen.hh"
#include "piececount.hh"
#include "square.hh"

namespace zoor {

//
// using from STL
//
using std::vector;
using std::ifstream;
using std::string;
using std::istringstream;
using std::sort;
using std::unique;
using std::make_shared;
using std::getline;

////////////////////////////////////////////////////////////////////////////////
// static member definitions
////////////////////////////////////////////////////////////////////////////////

constexpr size_t FenSymbols::RANK_LENGTH;
constexpr size_t FenSymbols::CASTLE_LENGTH;
constexpr char FenSymbols::DASH;
const string FenSymbols::RANK_CHR("PNBRQKpnbrqk12345678");
const string FenSymbols::CASTLE_CHR("KQkq");
const string FenSymbols::COLOR_CHR("wb");

////////////////////////////////////////////////////////////////////////////////
// static function declarations
////////////////////////////////////////////////////////////////////////////////

namespace {

//
// helper functions for readFen(const string&)
//
size_t
readRank(const string &rankLine, vector<Square>& squareList, const dim_t row);
Color
readColor(const string &colorLine);
BoardInfo
readBoardInfo(string &infoLine);
PieceMove
readEnPassant(const string &field);

} // namespace

////////////////////////////////////////////////////////////////////////////////
// function definitions
////////////////////////////////////////////////////////////////////////////////

//
// readFen with param ifstream.
//
vector<FenRecord>
readFen(ifstream &inFile)
{
  string line;
  vector<FenRecord> fenList;

  while (getline(inFile, line)) {
    if (line.empty()) continue;
    auto fenrec = readFenLine(line);
    fenList.push_back(fenrec);
  }

  if (inFile.fail() and not inFile.eof())
    throw ChessError("Error processing FEN file");

  return fenList;
}

//
// readFen with param string.
//
const FenRecord
readFenLine(const string &fenLine)
{
  string buff;
  int numRank = 7;
  vector<Square> squareList;
  istringstream iss(fenLine);

  // process the last ranks, 8 through 2
  for (; numRank > 0; --numRank) {
    if (!getline(iss, buff, '/'))
      throw ChessError("FEN record is not valid");

    readRank(buff, squareList, numRank);
  }

  // process the 1st rank
  if (!(iss >> buff))
    throw ChessError("FEN record is not valid");

  readRank(buff, squareList, numRank);

  // check that number of pieces makes sense
  PieceCount pc(squareList);
  if (!pc.good())
    throw ChessError("FEN record is not valid");

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

  auto pmove = readEnPassant(buff);

  // process half moves
  size_t halfMoves;
  if (!(iss >> halfMoves))
    throw ChessError("FEN record is not valid");

  // process full moves
  size_t fullMoves;
  iss >> fullMoves;

  // can't use !(iss >> fullMove) above, because it will be true if eof
  if (iss.fail() && !iss.eof())
    throw ChessError("FEN record is not valid");

  auto pb = make_shared<Board>(squareList, color, info, pmove);

  return FenRecord(pb, halfMoves, fullMoves);
}

//
// convert a FEN symbol to a piece code
//
piece_t
fenPiece(char fenCode) noexcept
{
  // get the color
  Color color;
  if (std::islower(fenCode))
    color = Color::B;
  else {
    color = Color::W;
    fenCode = std::tolower(fenCode);
  }

  // get the piece type
  Piece piece;
  switch (fenCode) {
  case 'p':
    piece = Piece::P;
    break;
  case 'n':
    piece = Piece::N;
    break;
  case 'b':
    piece = Piece::B;
    break;
  case 'r':
    piece = Piece::R;
    break;
  case 'q':
    piece = Piece::Q;
    break;
  case 'k':
    piece = Piece::K;
    break;
  default:
    return 0;
  }

  return color | piece;
}

////////////////////////////////////////////////////////////////////////////////
// static function definitions
////////////////////////////////////////////////////////////////////////////////

namespace {

//! @brief Read the contents of one single rank from the first field in a FEN
//! record.
//! @details The assumptions are listed here:
//! @li Does not contain more than 8 characters.
//! @li Valid digits are 1 to 8, but if there are multiple digits their sum
//! cannot exceed 8.
//! @li The only valid letters are those that represent white or black pieces.
//! @param rankLine The string representing one rank.
//! @param squareList A reference to a vector of squares where squares are added.
//! @param row The number of row representing the current rank.
//! @return The total number of pieces found in the rank.
//! @throw ChessError if the rankLine violates any of the assumptions.
size_t
readRank(const string &rankLine, vector<Square> &squareList, const dim_t row)
{
  // check rank line is not empty and does not exceed max chars
  if (rankLine.empty() || rankLine.size() > FenSymbols::RANK_LENGTH)
    throw ChessError("FEN record is not valid");

  // check that we only have valid chars
  if (rankLine.find_first_not_of(FenSymbols::RANK_CHR) != string::npos)
    throw ChessError("FEN record is not valid");

  dim_t col = 0;
  size_t numPieces = 0;
  using len_type = decltype(FenSymbols::RANK_LENGTH);

  for (auto &c : rankLine) {
    // check for empty squares
    if (c >= '1' && c <= '8') {
      col += c - '0';
      continue;
    }

    if (static_cast<len_type>(col) >= FenSymbols::RANK_LENGTH)
      throw ChessError("FEN record is not valid");

    // convert code to piece
    auto code = fenPiece(c);
    squareList.emplace_back(row, col, code);
    ++col;
    ++numPieces;
  }

  // check that we processed 8 squares
  if (col != FenSymbols::RANK_LENGTH)
    throw ChessError("FEN record is not valid");

  return numPieces;
}

//! @brief Reads the color of the player who moves next.
//! @details The assumptions are:
//! @li Contains exactly one character.
//! @li Valid characters are <em>w</em> and <em>b</em>.
//! @param colorLine The string representing the color.
//! @return The @c Color for black or white.
//! @throw ChessError if the rankLine violates any of the assumptions.
Color
readColor(const string &colorLine)
{
  if (colorLine.size() != 1)
    throw ChessError("FEN record is not valid");

  if (colorLine.find_first_not_of(FenSymbols::COLOR_CHR) != string::npos)
    throw ChessError("FEN record is not valid");

  return colorLine.front() == 'w' ? Color::W : Color::B;
}

//! @brief Read the castling rights from the 3rd field in a FEN record.
//! @details The assumptions are:
//! @li Does not contain more than 4 characters.
//! @li Legal characters are -, K, Q, k, and q.
//! @li If - is present, then this should be the only character available.
//! @li Valid characters should not repeat.
//! @param infoLine The string representing the castling rights. Should not be
//! marked as const, because it is sorted in order to find unique values in
//! string.
//! @return A @c BoardInfo representing the castling rights.
//! @throw ChessError if the infoLine violates any of the assumptions.
BoardInfo
readBoardInfo(string &infoLine)
{
  // check info line is not empty and does not exceed max chars
  if (infoLine.empty() || infoLine.size() > FenSymbols::CASTLE_LENGTH)
    throw ChessError("FEN record is not valid");

  if (infoLine.size() == 1 && infoLine.front() == FenSymbols::DASH) {
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
    info.rookH8On();

  // remove long castling for black
  if (!bCastleLong)
    info.rookA8On();

  return info;
}

//! @brief Read en passant info from the 4th field in a FEN record.
//! @details The assumptions are:
//! @li Does not contain more than 2 characters.
//! @li Legal characters are -, a-h, 3, and 6.
//! @li If - is present, then the field should not contain more chars.
//! @li If - is not present, then the field should contain 2 chars, the first
//! should be a letter in a-h, and second should be 3 or 6.
//! @details If there is an en passant, then the caller of this function should
//! enforce that there is a pawn that makes this info true.
//! @param field The string representing the 4th field in the FEN record.
//! @return A @c PieceMove representing the last move.
//! @throw ChessError if the field violates any of the assumptions.
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
  dim_t col = colChr - 'a';

  // check row number is valid
  auto rowChr = field.back();
  if (rowChr != '3' && rowChr != '6')
    throw ChessError("FEN record is not valid");

  // set the row numbers and the piece code
  piece_t code;
  dim_t fromRow, toRow;

  if (rowChr == '3') {
    fromRow = 1;
    toRow = 3;
    code = Color::W | Piece::P;
  } else {
    fromRow = 6;
    toRow = 4;
    code = Color::B | Piece::P;
  }

  return PieceMove(fromRow, col, code, toRow, col);
}

} // namespace

} // zoor
