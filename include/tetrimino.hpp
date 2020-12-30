#pragma once

#include "board.hpp"
#include "entity.hpp"
#include "vec2d.hpp"
#include <Windows.h>
#include <memory>

class Tetrimino : public Entity {
public:
  explicit Tetrimino(std::vector<Vec2d> points);

  static std::unique_ptr<Tetrimino> create(char type);

  void draw(ScreenBuffer &buffer) const override;
  void update(double delta_seconds) override;

  void set_board(Board *board) { _board = board; }

private:
  bool is_blocked(const Vec2d &dir) const;

  std::vector<Vec2d> points_to_draw() const;

  void rotate();

  std::vector<Vec2d> _points;
  double _fall_delay = 0.0;
  bool is_pressed = true;
  Board *_board = nullptr;
};