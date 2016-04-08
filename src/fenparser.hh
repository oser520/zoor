/**
 * @file feninput.hh
 * @author Omar A Serrano
 * @date 2016-04-07
 */
#ifndef _FENINPUT_H
#define _FENINPUT_H

#include <string>
#include <fstream>

#include "board.hh"

namespace zoor {

class FenInput
{
public:
  // copy control
  FenInput() = delete;
  FenInput(const char *fileName);
  FenInput(const std::string &fileName);
  FenInput& operator=(const FenInput &fenInput) = delete;
  FenInput& operator=(FenInput &&fenInput) noexcept = default;
  ~FenInput() noexcept;

  // interface
  std::vector<Board> getBoards();

private:
  bool mIsOpen;
  std::ifstream mFile;
};

}

#endif // _FENINPUT_H
