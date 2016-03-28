/**
 * @file boardinfo.cc
 * @author Omar A Serrano
 * @date 2016-03-27
 */

#include <string>
#include <iostream>
#include <sstream>

namespace zoor {

/**
 * @return A reference to the underlying bitset used.
 * @throw Never throws.
 */
inline const BoardInfo::bitset_type BoardInfo::get() const noexcept
{
  return mInfo;
}

/**
 * @return True if the rook at A1 has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::rookA1() const noexcept
{
  return mInfo[RK_A1_MOVED];
}

/**
 * @brief Turn on the bit for rook A1.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::rookA1On() noexcept
{
  mInfo.set(RK_A1_MOVED);
  return *this;
}

/**
 * @return True if the rook at H1 has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::rookH1() const noexcept
{
  return mInfo[RK_H1_MOVED];
}

/**
 * @brief Turn on the bit for rook H1.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::rookH1On() noexcept
{
  mInfo.set(RK_H1_MOVED);
  return *this;
}

/**
 * @return True if the white king has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::wkMoved() const noexcept
{
  return mInfo[WK_MOVED];
}

/**
 * @brief Turn on the bit for white king has moved.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::wkMovedOn() noexcept
{
  mInfo.set(WK_MOVED);
  return *this;
}

/**
 * @return True if the white king is in check, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::wkCheck() const noexcept
{
  return mInfo[WK_CHECK];
}

/**
 * @brief Set the bit for the white king in check.
 * @param value True if the king is in check, false otherwise.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& Board::wkCheckSet(bool value) noexcept
{
  mInfo.set(WK_CHECK, value);
  return *this;
}

/**
 * @return True if it is mate for the white king, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::wkMate() const noexcept
{
  return mInfo[WK_MATE];
}

/**
 * @brief Turn on the bit for mate for the white king.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::wkMateOn() noexcept
{
  mInfo.set(WK_MATE);
  return *this;
}

/**
 * @return True if the white king can castle, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::wkCastle() const noexcept
{
  bool value = mInfo[RK_H1_MOVED];
  value |= mInfo[WK_MOVED];
  value |= mInfo[WK_CHECK];
  value |= mInfo[WK_MATE];
  return !value;
}

/**
 * @return True if the white king can castle long, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::wkCastleLong() const noexcept
{
  bool value = mInfo[RK_A1_MOVED];
  value |= mInfo[WK_MOVED];
  value |= mInfo[WK_CHECK];
  value |= mInfo[WK_MATE];
  return !value;
}

/**
 * @return True if the rook at A8 has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::rookA8() const noexcept
{
  return mInfo[RK_A1_MOVED];
}

/**
 * @brief Turn on the bit for rook A8.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::rookA8On() noexcept
{
  mInfo.set(RK_A8_MOVED);
  return *this;
}

/**
 * @return True if the rook at H8 has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::rookH8() const noexcept
{
  return mInfo[RK_H8_MOVED];
}

/**
 * @brief Turn on the bit for rook H8.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::rookH8On() noexcept
{
  mInfo.set(RK_H8_MOVED);
  return *this;
}

/**
 * @return True if the black king has moved, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::bkMoved() const noexcept
{
  return mInfo[BK_MOVED];
}

/**
 * @brief Turn on the bit for black king has moved.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::bkMovedOn() noexcept
{
  mInfo.set(BK_MOVED);
  return *this;
}

/**
 * @return True if the black king is in check, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::bkCheck() const noexcept
{
  return mInfo[BK_CHECK];
}

/**
 * @brief Set the bit for the black king in check.
 * @param value True if the king is in check, false otherwise.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::bkCheckSet(bool value) noexcept
{
  mInfo.set(BK_CHECK, value);
  return *this;
}

/**
 * @return True if it is mate for the black king, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::bkMate() const noexcept
{
  return mInfo[BK_MATE];
}

/**
 * @brief Turn on the bit for mate for the black king.
 * @detail This action is irreversible.
 * @return A reference to this @c BoardInfo.
 * @throw Never throws.
 */
inline BoardInfo& BoardInfo::bkMateOn() noexcept
{
  mInfo.set(BK_MATE);
  return *this;
}

/**
 * @return True if the black king can castle, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::bkCastle() const noexcept
{
  bool value = mInfo[RK_H8_MOVED];
  value |= mInfo[BK_MOVED];
  value |= mInfo[BK_CHECK];
  value |= mInfo[BK_MATE];
  return !value;
}

/**
 * @return True if the black king can castle long, false otherwise.
 * @throw Never throws.
 */
inline bool BoardInfo::bkCastleLong() const noexcept
{
  bool value = mInfo[RK_A8_MOVED];
  value |= mInfo[BK_MOVED];
  value |= mInfo[BK_CHECK];
  value |= mInfo[BK_MATE];
  return !value;
}

/**
 * @return A string representation of the @c BoardInfo.
 * @details The representation is the same as the string representation for the
 * underlying bitset.
 */
std::string BoardInfo::toString() const
{
  std::ostringstream oss;
  oss << get();
  return oss.str();
}

/**
 * @return The hash code for the @c BoardInfo.
 * @throw Never throws.
 */
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

/**
 * @brief Equality operator for @c BoardInfo.
 * @param info1 The left hand @c BoardInfo.
 * @param info2 The right hand @c BoardInfo.
 * @return Ture if they are equal, false otherwise.
 * @throw Never throws.
 */
inline bool operator==(const BoardInfo& info1, const BoardInfo& info2) noexcept
{
  return info1.get() == info2.get();
}

/**
 * @brief Non-equality operator for @c BoardInfo.
 * @param info1 The left hand @c BoardInfo.
 * @param info2 The right hand @c BoardInfo.
 * @return Ture if they are not equal, false otherwise.
 * @throw Never throws.
 */
inline bool operator!=(const BoardInfo& info1, const BoardInfo& info2) noexcept
{
  return !(info1 == info2);
}

/**
 * @brief The output operator for @c BoardInfo.
 * @param os The output stream.
 * @param info The @c BoardInfo.
 * @return A reference to the output stream.
 * @throw Never throws.
 */
inline std::ostream& operator<<(std::ostream& os, const BoardInfo& info)
{
  os << info.get();
  return os;
}

} // zoor
