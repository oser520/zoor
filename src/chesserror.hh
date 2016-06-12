////////////////////////////////////////////////////////////////////////////////
/// @file chesserror.hh
/// @author Omar A Serrano
/// @date 2016-02-28
////////////////////////////////////////////////////////////////////////////////
#ifndef _CHESSERROR_H
#define _CHESSERROR_H

//
// STL
//
#include <stdexcept>
#include <string>

namespace zoor {

///
/// @brief A simple exception class to represent chess errors.
///
class ChessError
  : public std::logic_error
{
public:
  ///
  /// @brief Default ctor.
  ///
  ChessError(): std::logic_error("Bad chess logic") {}

  ///
  /// @brief Constructor.
  /// @param msg The exception message.
  ///
  explicit
  ChessError(const char *msg): std::logic_error(msg) {}

  ///
  /// @brief Constructor.
  /// @param msg The exception message.
  ///
  explicit
  ChessError(const std::string &msg): std::logic_error(msg) {}
};

} // zoor
#endif /* _CHESSERROR_H */
