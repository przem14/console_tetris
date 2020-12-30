#pragma once

#include "entity.hpp"
#include "screen_buffer.hpp"
#include "text_utils.hpp"
#include <algorithm>
#include <array>

class GameController;

class Board : public Entity {
public:
  explicit Board(GameController &game_controller);

  void draw(ScreenBuffer &buffer) const override;

  bool is_blocked(const Vec2d &p) const;

  void insert(const std::vector<Vec2d> &points, const Vec2d &transform,
              int drop_level);

private:
  int remove_full_rows();
  void clear_board();

  std::array<std::array<_TCHAR, 20>, 16> _board;
  GameController &_game_controller;
};