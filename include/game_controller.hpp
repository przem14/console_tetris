#pragma once

#include "board.hpp"
#include "entity.hpp"
#include "label.hpp"
#include "tetrimino.hpp"
#include <memory>
#include <random>
#include <time.h>

class GameController : public Entity {
public:
  GameController();

  void draw(ScreenBuffer &buffer) const override;
  void update(double delta_seconds) override;

  void next_tetrimino();
  void update_score(int value);
  void game_over() { start_game(); }

private:
  void start_game();
  void connect_tetrimino_with_board();

  std::unique_ptr<Tetrimino> create_tetrimino() {
    return Tetrimino::create(_types[_distribution(_generator)]);
  }

  std::unique_ptr<Label> _small_title_label;
  std::unique_ptr<ValueLabel> _score_label;
  std::unique_ptr<Label> _next_label;
  std::unique_ptr<Board> _board;
  std::unique_ptr<Tetrimino> _tetrimino;
  std::unique_ptr<Tetrimino> _next_tetrimino;

  std::default_random_engine _generator;
  std::uniform_int_distribution<int> _distribution{0, 6};
  std::array<char, 7> _types{'T', 'I', 'S', 'Z', 'L', 'J', 'O'};
};