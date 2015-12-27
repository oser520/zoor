/**
 * @file board.cc
 * @author Omar A Serrano
 * @date 2015-12-26
 */

/**
 * TODO: determine how to initialize default board.
 */
Board::Board() {}

/**
 * TODO: implement moves function
 */
vector<Board> Board::moves() const noexcept
{
  return vector<Board>();
}

/**
 * TODO: implement output operator for Board
 */
std:ostream& operator<<(std:ostream &os, const Board &board)
{
  return os;
}

bool operator==(const Board &boar1, const Board &board2) noexcept
{
  return board1.mColorMove == board2.mColorMove
      && equal(begin(board1), end(board1), begin(board2));
}

/**
 * TODO: implement non-equality operator.
 */
bool operator!=(const Board &boar1, const Board &board2) noexcept;
