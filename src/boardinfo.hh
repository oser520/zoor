////////////////////////////////////////////////////////////////////////////////
/// @file boardinfo.hh
/// @author Omar A Serrano
/// @date 2016-03-27
////////////////////////////////////////////////////////////////////////////////
#ifndef _BOARDINFO_H
#define _BOARDINFO_H

//
// STL headers
//
#include <bitset>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

namespace zoor {

////////////////////////////////////////////////////////////////////////////////
// declarations
////////////////////////////////////////////////////////////////////////////////

///
/// @brief Used to maintain information to determine if certain moves are legal.
/// @details Maintains information about the kings and the rooks, including if
/// any of them have moved, if either of the kings are in check, or if it is
/// mate for one of them.
///
class BoardInfo
{

  // The number of bits needed by the bitset.
  enum { NUMBITS = 10};

public:

  ///
  /// @brief Default ctor.
  /// @details Initializes @c BoardInfo with all castling rights.
  /// @throw Never throws.
  ///
  BoardInfo() noexcept = default;

  ///
  /// @brief Default copy ctor.
  /// @param info The @c BoardInfo to copy.
  /// @throw Never throws.
  ///
  BoardInfo(const BoardInfo& info) noexcept = default;

  ///
  /// @brief Default move ctor.
  /// @param info The @c BoardInfo to move.
  /// @throw Never throws.
  ///
  BoardInfo(BoardInfo&& info) noexcept = default;

  ///
  /// @brief Default copy assignment.
  /// @param info The @c BoardInfo to copy.
  /// @throw Never throws.
  ///
  BoardInfo& operator=(const BoardInfo& info) noexcept = default;

  ///
  /// @brief Default move assignment.
  /// @param info The @c BoardInfo to move.
  /// @throw Never throws.
  ///
  BoardInfo& operator=(BoardInfo&& info) noexcept = default;

  ///
  /// @brief Default dtor.
  /// @throw Never throws.
  ///
  ~BoardInfo() noexcept = default;

  ///
  /// @brief Alias for the type of bitset used here.
  ///
  using bitset_type = std::bitset<NUMBITS>;

  ///
  /// @brief Access the underlying bitset.
  ///
  const bitset_type get() const noexcept;

  //
  // Access and getters for info about the white king and rooks.
  //
  bool rookA1() const noexcept;
  BoardInfo& rookA1On() noexcept;
  bool rookH1() const noexcept;
  BoardInfo& rookH1On() noexcept;
  bool wkMoved() const noexcept;
  BoardInfo& wkMovedOn() noexcept;
  bool wkCheck() const noexcept;
  BoardInfo& wkCheckSet(bool value) noexcept;
  bool wkMate() const noexcept;
  BoardInfo& wkMateOn() noexcept;
  bool wkCastle() const noexcept;
  bool wkCastleLong() const noexcept;

  //
  // Access and getters for info about the black king and rooks.
  //
  bool rookA8() const noexcept;
  BoardInfo& rookA8On() noexcept;
  bool rookH8() const noexcept;
  BoardInfo& rookH8On() noexcept;
  bool bkMoved() const noexcept;
  BoardInfo& bkMovedOn() noexcept;
  bool bkCheck() const noexcept;
  BoardInfo& bkCheckSet(bool value) noexcept;
  bool bkMate() const noexcept;
  BoardInfo& bkMateOn() noexcept;
  bool bkCastle() const noexcept;
  bool bkCastleLong() const noexcept;

  //
  // General utility functions.
  //
  std::string toString() const;
  size_t hashCode() const noexcept;

private:
  //
  // @brief Maintains information about the kings and rooks.
  // @details Maintains the following information:
  // @li 1. The rook at <em>a1</em> has moved.
  // @li 2. The rook at <em>h1</em> has moved.
  // @li 3. The white king has moved.
  // @li 4. The white king is in check.
  // @li 5. Mate for white king.
  // @li 6. The rook at <em>a8</em> has moved.
  // @li 7. The rook at <em>h8</em> has moved.
  // @li 8. The black king has moved.
  // @li 9. The black king is in check.
  // @li 10. Mate for black king.
  //
  bitset_type mInfo;

  //
  // Indexes for the bits in <em>mInfo</em>.
  //
  enum {
    RK_A1_MOVED, RK_H1_MOVED, WK_MOVED, WK_CHECK, WK_MATE,
    RK_A8_MOVED, RK_H8_MOVED, BK_MOVED, BK_CHECK, BK_MATE
  };
};

//
// Non member operator functions for @c BoardInfo.
//
bool
operator==(const BoardInfo& info1, const BoardInfo& info2) noexcept;

bool
operator!=(const BoardInfo& info1, const BoardInfo& info2) noexcept;

std::ostream&
operator<<(std::ostream& os, const BoardInfo& info);

////////////////////////////////////////////////////////////////////////////////
// definitions
////////////////////////////////////////////////////////////////////////////////

///
/// @return A reference to the underlying bitset used.
/// @throw Never throws.
///
inline const BoardInfo::bitset_type
BoardInfo::get() const noexcept
{
  return mInfo;
}

///
/// @return True if the rook at A1 has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::rookA1() const noexcept
{
  return mInfo[RK_A1_MOVED];
}

///
/// @brief Turn on the bit for rook A1.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::rookA1On() noexcept
{
  mInfo.set(RK_A1_MOVED);
  return *this;
}

///
/// @return True if the rook at H1 has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::rookH1() const noexcept
{
  return mInfo[RK_H1_MOVED];
}

///
/// @brief Turn on the bit for rook H1.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::rookH1On() noexcept
{
  mInfo.set(RK_H1_MOVED);
  return *this;
}

///
/// @return True if the white king has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::wkMoved() const noexcept
{
  return mInfo[WK_MOVED];
}

///
/// @brief Turn on the bit for white king has moved.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::wkMovedOn() noexcept
{
  mInfo.set(WK_MOVED);
  return *this;
}

///
/// @return True if the white king is in check, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::wkCheck() const noexcept
{
  return mInfo[WK_CHECK];
}

///
/// @brief Set the bit for the white king in check.
/// @param value True if the king is in check, false otherwise.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::wkCheckSet(bool value) noexcept
{
  mInfo.set(WK_CHECK, value);
  return *this;
}

///
/// @return True if it is mate for the white king, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::wkMate() const noexcept
{
  return mInfo[WK_MATE];
}

///
/// @brief Turn on the bit for mate for the white king.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::wkMateOn() noexcept
{
  mInfo.set(WK_MATE);
  return *this;
}

///
/// @return True if the white king can castle, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::wkCastle() const noexcept
{
  bool value = mInfo[RK_H1_MOVED];
  value |= mInfo[WK_MOVED];
  value |= mInfo[WK_CHECK];
  value |= mInfo[WK_MATE];
  return !value;
}

///
/// @return True if the white king can castle long, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::wkCastleLong() const noexcept
{
  bool value = mInfo[RK_A1_MOVED];
  value |= mInfo[WK_MOVED];
  value |= mInfo[WK_CHECK];
  value |= mInfo[WK_MATE];
  return !value;
}

///
/// @return True if the rook at A8 has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::rookA8() const noexcept
{
  return mInfo[RK_A8_MOVED];
}

///
/// @brief Turn on the bit for rook A8.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::rookA8On() noexcept
{
  mInfo.set(RK_A8_MOVED);
  return *this;
}

///
/// @return True if the rook at H8 has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::rookH8() const noexcept
{
  return mInfo[RK_H8_MOVED];
}

///
/// @brief Turn on the bit for rook H8.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::rookH8On() noexcept
{
  mInfo.set(RK_H8_MOVED);
  return *this;
}

///
/// @return True if the black king has moved, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::bkMoved() const noexcept
{
  return mInfo[BK_MOVED];
}

///
/// @brief Turn on the bit for black king has moved.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::bkMovedOn() noexcept
{
  mInfo.set(BK_MOVED);
  return *this;
}

///
/// @return True if the black king is in check, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::bkCheck() const noexcept
{
  return mInfo[BK_CHECK];
}

///
/// @brief Set the bit for the black king in check.
/// @param value True if the king is in check, false otherwise.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::bkCheckSet(bool value) noexcept
{
  mInfo.set(BK_CHECK, value);
  return *this;
}

///
/// @return True if it is mate for the black king, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::bkMate() const noexcept
{
  return mInfo[BK_MATE];
}

///
/// @brief Turn on the bit for mate for the black king.
/// @details This action is irreversible.
/// @return A reference to this @c BoardInfo.
/// @throw Never throws.
///
inline BoardInfo&
BoardInfo::bkMateOn() noexcept
{
  mInfo.set(BK_MATE);
  return *this;
}

///
/// @return True if the black king can castle, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::bkCastle() const noexcept
{
  bool value = mInfo[RK_H8_MOVED];
  value |= mInfo[BK_MOVED];
  value |= mInfo[BK_CHECK];
  value |= mInfo[BK_MATE];
  return !value;
}

///
/// @return True if the black king can castle long, false otherwise.
/// @throw Never throws.
///
inline bool
BoardInfo::bkCastleLong() const noexcept
{
  bool value = mInfo[RK_A8_MOVED];
  value |= mInfo[BK_MOVED];
  value |= mInfo[BK_CHECK];
  value |= mInfo[BK_MATE];
  return !value;
}

///
/// @return A string representation of the @c BoardInfo.
/// @details The representation is the same as the string representation for the
/// underlying bitset.
///
inline
std::string BoardInfo::toString() const
{
  std::ostringstream oss;
  oss << get();
  return oss.str();
}

///
/// @return The hash code for the @c BoardInfo.
/// @throw Never throws.
///
inline
size_t BoardInfo::hashCode() const noexcept
{
  // hash the first 5 bits
  size_t h = mInfo.to_ulong() & 0x1f;
  h += h << 10;
  h ^= h >> 6;

  // hash the last 5 bits
  h += mInfo.to_ulong() & 0x1f0;
  h += h << 10;
  h ^= h >> 6;

  h += h << 3;
  h += h >> 11;
  h += h << 15;

  return h;
}

///
/// @brief Equality operator for @c BoardInfo.
/// @param info1 The left hand @c BoardInfo.
/// @param info2 The right hand @c BoardInfo.
/// @return Ture if they are equal, false otherwise.
/// @throw Never throws.
///
inline bool
operator==(const BoardInfo& info1, const BoardInfo& info2) noexcept
{
  return info1.get() == info2.get();
}

///
/// @brief Non-equality operator for @c BoardInfo.
/// @param info1 The left hand @c BoardInfo.
/// @param info2 The right hand @c BoardInfo.
/// @return Ture if they are not equal, false otherwise.
/// @throw Never throws.
///
inline bool
operator!=(const BoardInfo& info1, const BoardInfo& info2) noexcept
{
  return !(info1 == info2);
}

///
/// @brief The output operator for @c BoardInfo.
/// @param os The output stream.
/// @param info The @c BoardInfo.
/// @return A reference to the output stream.
/// @throw Never throws.
///
inline std::ostream&
operator<<(std::ostream& os, const BoardInfo& info)
{
  os << info.get();
  return os;
}

} // zoor

//
// Open standard namespace to specialize STL template.
//
namespace std {

//
// Specialize hash template for @c BoardInfo.
//
template<>
struct hash<zoor::BoardInfo>
{
  using argument_type = zoor::BoardInfo;
  using result_type = size_t;

  result_type operator()(const argument_type& arg)
  {
    return arg.hashCode();
  }
};
} // std
#endif // _BOARDINFO_H
