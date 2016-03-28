/**
 * @file boardinfo.cc
 * @author Omar A Serrano
 * @date 2016-03-27
 */

#include <string>
#include <iostream>

namespace zoor {

const bitset_type BoardInfo::get() const noexcept;

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

std::string toString() const;
size_t hashCode() const noexcept;

bool operator==(const BoardInfo& info1, const BoardInfo& info2) noexcept;
bool operator!=(const BoardInfo& info1, const BoardInfo& info2) noexcept;
std::ostream& operator<<(std::ostream& os, const BoardInfo& info) noexcept;

} // zoor
