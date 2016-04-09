/**
 * @file notation.hh
 * @author Omar A Serrano
 * @date 2016-04-07
 */
#ifndef _NOTATION_H
#define _NOTATION_H

#include <string>
#include <vector>
#include <fstream>

#include "board.hh"

/**
 * Example of FEN records.
 *
 * FEN record for starting position:
 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 *
 * After the move 1. e4:
 * rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
 *
 * After the move 1. .. c5:
 * rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
 *
 * After the move 2. Nf3:
 * rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
 */

namespace zoor {

/**
 * @brief A POD (plain old data) with symbols that are used in FEN notation.
 * @details Used to parse files with FEN notation. If this POD was long lived, then
 * it might make sense to make its members static; however, it is very unlikely to
 * have a frequent need to read files with FEN notation.
 */
struct FenSymbols
{
  /**
   * @brief Default ctor.
   */
  FenSymbols()
    : wPiece("RNBQK"),
      bPiece("rnbqk"),
      wCastle("KQ"),
      bCastle("kq") {}

  /**
   * @brief Default copy ctor.
   */
  FenSymbols(const FenSymbols &fenSymbols) = default;

  /**
   * @brief Default move ctor.
   */
  FenSymbols(FenSymbols &&fenSymbols) noexcept = default;

  /**
   * @brief Default copy assignment.
   */
  FenSymbols& operator=(const FenSymbols &fenSymbols) = default;

  /**
   * @brief Default move assignment.
   */
  FenSymbols& operator=(FenSymbols &&fenSymbols) noexcept = default;

  /**
   * @brief Default dtor.
   */
  ~FenSymbols() noexcept = default;

  /**
   * @brief Symbols for white pieces.
   */
  const std::string wPiece;

  /**
   * @brief Symbols for black pieces.
   */
  const std::string bPiece;

  /**
   * @brief Symbols for white can castle.
   */
  const std::string wCastle;

  /**
   * @brief Symbols for black can castle.
   */
  const std::string bCastle;

  /**
   * @brief Symbol for white's turn.
   */
  constexpr char cWhite('w');

  /**
   * @brief Symbol for black's turn.
   */
  constexpr char cBlack('b');

  /**
   * @brief Symbol for rank divider.
   */
  constexpr char slash('/');

  /**
   * @brief Symbols for field divider.
   */
  constexpr char space(' ');
};

/**
 * @brief Read a chess position in FEN notation from a string.
 * @details If the string contains more than a FEN record, but the record begins
 * with a valid FEN record, then whatever else remains after the FEN record is
 * ignored.
 * @param fenLine A FEN record string.
 * @return A vector of boards.
 */
Board readFEN(std::string &fenLine);

/**
 * @brief Read a chess position in FEN notation from a file.
 * @param inFile The name of the file.
 * @return A vector of boards.
 */
std::vector<Board> readFEN(std::ifstream &inFile);

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
