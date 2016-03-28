/**
 * @file boardinfo.hh
 * @author Omar A Serrano
 * @date 2016-03-27
 */
#ifndef _BOARDINFO_H
#define _BOARDINFO_H

#include <bitset>
#include <string>
#include <iostream>
#include <functional>

namespace zoor {

/**
 * @brief Used to maintain information to determine if certain moves are legal.
 * @details Maintains information about the kings and the rooks, including if
 * any of them have moved, if either of the kings are in check, or if it is
 * mate for one of them.
 */
class BoardInfo
{
  /**
   * The number of bits needed by the bitset.
   */
  enum { NUMBITS = 10};

public:

  /**
   * Copy control
   */
  BoardInfo() noexcept = default;
  BoardInfo(const BoardInfo& info) noexcept = default;
  BoardInfo(BoardInfo&& info) noexcept = default;
  BoardInfo& BoardInfo(const BoardInfo& info) noexcept = default;
  BoardInfo& BoardInfo(BoardInfo&& info) noexcept = default;
  ~BoardInfo() noexcept = default;

  /**
   * Alias for the type of bitset used here.
   */
  using bitset_type = std::bitset<NUMBITS>;

  /**
   * Access and getters for info about white the white king and rooks.
   */
  const bitset_type get() const noexcept;

  /**
   * Access and getters for info about white the white king and rooks.
   */
  bool rookA1() const noexcept;
  bool rookA1On() noexcept;
  bool rookH1() const noexcept;
  bool rookH1On() noexcept;
  bool wkMoved() const noexcept;
  bool wkMovedOn() noexcept;
  bool wkCheck() const noexcept;
  bool wkCheckSet(bool value) const noexcept;
  bool wkMate() const noexcept;
  bool wkMateOn() noexcept;
  bool wkCastle() const noexcept;
  bool wkCastleLong() const noexcept;

  /**
   * Access and getters for info about the black king and rooks.
   */
  bool rookA8() const noexcept;
  bool rookA8On() noexcept;
  bool rookH8() const noexcept;
  bool rookH8On() noexcept;
  bool bkMoved() const noexcept;
  bool bkMovedOn() noexcept;
  bool bkCheck() const noexcept;
  bool bkCheckSet(bool value) const noexcept;
  bool bkMate() const noexcept;
  bool bkMateOn() noexcept;
  bool bkCastle() const noexcept;
  bool bkCastleLong() const noexcept;

  /**
   * General utility functions.
   */
  std::string toString() const;
  size_t hashCode() const noexcept;

private:
  /**
   * @brief Maintains information about the kings and rooks.
   * @detail Maintains the following information:
   * @li 1. The rook at <em>a1</em> has moved.
   * @li 2. The rook at <em>h1</em> has moved.
   * @li 3. The white king has moved.
   * @li 4. The white king is in check.
   * @li 5. Mate for white king.
   * @li 6. The rook at <em>a8</em> has moved.
   * @li 7. The rook at <em>h8</em> has moved.
   * @li 8. The black king has moved.
   * @li 9. The black king is in check.
   * @li 10. Mate for black king.
   */
  bitset_type mInfo;

  /**
   * Indexes for the bits in <em>mInfo</em>.
   */
  enum {
    RK_A1_MOVED, RK_H1_MOVED, WK_MOVED, WK_CHECK, WK_MATE,
    RK_A8_MOVED, RK_H8_MOVED, BK_MOVED, BK_CHECK, BK_MATE
  };
};

/**
 * Non member operator functions for @c BoardInfo.
 */
bool operator==(const BoardInfo& info1, const BoardInfo& info2) noexcept;
bool operator!=(const BoardInfo& info1, const BoardInfo& info2) noexcept;
std::ostream& operator<<(std::ostream& os, const BoardInfo& info) noexcept;

/**
 * Open standard namespace to specialize STL template.
 */
namespace std {

/**
 * Specialize hash template for @c BoardInfo.
 */
template<>
struct hash<zoor::BoardInfo>
{
  argument_type = zoor::BoardInfo;
  result_type = size_t;

  result_type operator()(const argument_type& arg)
  {
    return arg.hashCode();
  }
};
} // std

} // zoor
#endif // _BOARDINFO_H
