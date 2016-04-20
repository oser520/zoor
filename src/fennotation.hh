/////////////////////////////////////////////////////////////////////////////////////
/// @file fennotation.hh
/// @author Omar A Serrano
/// @date 2016-04-07
///
/// @details Functions and objects to create boards from a file that contains records
/// written in Forsyth-Edwards notation (FEN), and to write FEN records from a given
/// board.
///
/// The following are examples of FEN records.
/// FEN record for starting position:
/// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
///
/// After the move 1. e4:
/// rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
///
/// After the move 1. .. c5:
/// rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
///
/// After the move 2. Nf3:
/// rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _FENNOTATION_H
#define _FENNOTATION_H

//
// STL headers
//
#include <string>
#include <vector>
#include <fstream>

//
// zoor headers
//
#include "fenrecord.hh"

namespace zoor {

/////////////////////////////////////////////////////////////////////////////////////
// Declarations.
/////////////////////////////////////////////////////////////////////////////////////

///
/// @brief FenSymbols contains static members that are used by functions to parse a
/// FEN record and build a board from it.
/// @details Copy control for FenSymbols has been removed, because it is not meant to
/// instantiated.
///
struct FenSymbols
{
  // Remove copy control
  FenSymbols() = delete;
  FenSymbols(const FenSymbols&) = delete;
  FenSymbols(FenSymbols&&) = delete;
  FenSymbols& operator=(const FenSymbols&) = delete;
  FenSymbols& operator=(FenSymbols&&) = delete;

  /// @brief The maximum number of chars that can be on a rank.
  static constexpr size_t RANK_LENGTH(8);

  /// @brief The maximum number of chars that can be on the 3rd field of a FEN
  /// record.
  static constexpr size_t CASTLE_LENGTH(4);

  /// @brief The char symbols for valid pieces.
  static const std::string RANK_CHR;

  /// @brief The char symbols to represent castling rights in the 3rd field of a FEN
  /// record.
  static const std::string CASTLE_CHR;

  /// @brief The char symbols for a valid color.
  static const std::string COLOR_CHR;

  /// @brief Used in 3rd and 4th fields to indicate that there are no castling rights
  /// or that there is no en passant.
  static constexpr char DASH('-');
};

///
/// @brief Read a chess position in FEN notation from a string.
/// @details If the string contains more than a FEN record, but the record begins
/// with a valid FEN record, then the record is consumed and whatever else remains
/// is ignored.
/// @param fenLine A FEN record string.
/// @return A @c FenRecord.
/// @throw ChessError if the FEN record is not valid.
///
const FenRecord
readFEN(const std::string &fenLine);

///
/// @brief Read a chess position in FEN notation from a file.
/// @param inFile The name of the file.
/// @return A vector of @c FenRecord.
///
std::vector<FenRecord>
readFEN(std::ifstream &inFile);

///
/// @brief Read a chess position FEN notation from a file.
/// @param fileName The name of the file.
/// @return A vector of @c FenRecord, which may contain 0 or more @c FenRecord.
///
std::vector<FenRecord>
readFEN(const char *fileName);

///
/// @copydoc readFEN(const char*)
///
std::vector<FenRecord>
readFEN(const std::string &fileName);

///
/// @brief Write a board to a file in FEN notation.
/// @param fileName The name of the file.
/// @param board The @c Board to be written.
///
void
writeFEN(const char *fileName, const Board &board);

///
/// @brief Write a board to a file in FEN notation.
/// @param fileName The name of the file.
/// @param boardList A vector of boards, each of which gets one line.
///
void
writeFEN(const char *fileName, const std::vector<Board> &boardList);

///
/// @copydoc writeFen(const char*,const &)
///
void
writeFEN(const std::string &fileName, const Board &board);

///
/// @copydoc writeFen(const char*,const std::vector<Board>&)
///
void
writeFEN(const std::string &fileName, const std::vector<Board> &boardList);

///
/// @brief Get the piece code from a FEN piece.
/// @param fenCode The symbol representing a piece. For white pieces, legal values
/// are P, N, B, R, Q, and K. Black pieces use the same symbols in lowercase.
/// @return A piece code representing the piece and the color of the piece. If
/// fenCode is not a valid symbol for a piece, then the piece code is none.
/// @throw Never throws.
///
piececode_t
fenPiece(char fenCode) noexcept;

/////////////////////////////////////////////////////////////////////////////////////
// inline implementations
/////////////////////////////////////////////////////////////////////////////////////

//
// readFEN with param const char*
//
inline std::vector<FenRecord>
readFEN(const char *fileName)
{
  std::ifstream if(fileName);
  return readFEN(if);
}

//
// readFEN with param const std::string&
//
inline std::vector<FenRecord>
readFEN(const std::string &fileName)
{
  std::ifstream if(fileName);
  return readFEN(if);
}

} // namesapce zoor
#endif // _FENNOTATION_H
