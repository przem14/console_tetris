#include "board.hpp"
#include "game_controller.hpp"

Board::Board(GameController &game_controller)
    : _game_controller(game_controller) {
  clear_board();
}

void Board::draw(ScreenBuffer &buffer) const {
  static tstring h_border(22, Chars::BORDER);

  const auto p = location();
  buffer.write(p.x - 1, p.y - 1, h_border.data());
  for (int y = 0; y < _board.size(); ++y) {
    buffer.write(p.x - 1, p.y + y, Chars::BORDER);
    buffer.write(p.x, p.y + y,
                 tstring(_board[y].begin(), _board[y].end()).data());
    buffer.write(p.x + _board[y].size(), p.y + y, Chars::BORDER);
  }
  buffer.write(p.x - 1, p.y + _board.size(), h_border.data());
}

bool Board::is_blocked(const Vec2d &p) const {
  return p.y < 0 || p.y >= _board.size() || p.x < 0 ||
         p.x >= _board.front().size() || _board[p.y][p.x] != Chars::SPACE;
}

void Board::insert(const std::vector<Vec2d> &points, const Vec2d &transform,
                   int drop_level) {
  for (auto p : points) {
    p = p + transform;
    if (is_blocked(p)) {
      _game_controller.game_over();
      return;
    }
    _board[p.y][p.x] = Chars::BLOCK;
  }

  const int score = remove_full_rows();
  _game_controller.next_tetrimino();
  _game_controller.update_score(
      (score > 0 ? (int(std::pow(2, score)) * 10) : 0) +
      (_board.size() - drop_level));
}

int Board::remove_full_rows() {
  int current = _board.size() - 1;
  int empty = -1;
  int removed_rows_count = 0;
  while (current >= 0) {
    if (std::all_of(_board[current].begin(), _board[current].end(),
                    [](auto c) { return c != Chars::SPACE; })) {
      std::fill(_board[current].begin(), _board[current].end(), Chars::SPACE);
      ++removed_rows_count;
      if (empty < 0) {
        empty = current;
      }
    } else if (empty >= 0) {
      std::swap(_board[current], _board[empty]);
      --empty;
    }
    --current;
  }
  return removed_rows_count;
}

void Board::clear_board() {
  for (auto &a : _board) {
    std::fill(a.begin(), a.end(), Chars::SPACE);
  }
}