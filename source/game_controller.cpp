#include "game_controller.hpp"

GameController::GameController() {
  srand(time(NULL));
  start_game();
}

void GameController::draw(ScreenBuffer &buffer) const {
  _small_title_label->draw(buffer);
  _score_label->draw(buffer);
  _next_label->draw(buffer);
  _board->draw(buffer);
  _tetrimino->draw(buffer);
  _next_tetrimino->draw(buffer);
}

void GameController::update(double delta_seconds) {
  _board->update(delta_seconds);
  _tetrimino->update(delta_seconds);
}

void GameController::next_tetrimino() {
  _tetrimino = std::move(_next_tetrimino);
  connect_tetrimino_with_board();

  _next_tetrimino = create_tetrimino();
  _next_tetrimino->set_location({3, 7});
}

void GameController::update_score(int value) {
  _score_label->set_value(_score_label->value() + value);
}

void GameController::start_game() {
  _small_title_label = std::make_unique<Label>(_TEXT("CONSOLE TETRIS"));
  _score_label = std::make_unique<ValueLabel>(_TEXT("SCORE: "));
  _next_label = std::make_unique<Label>(_TEXT("NEXT:"));
  _board = std::make_unique<Board>(*this);

  _small_title_label->set_location({2, 0});
  _score_label->set_location({2, 2});
  _next_label->set_location({2, 5});
  _board->set_location({12, 5});

  _next_tetrimino = create_tetrimino();
  next_tetrimino();
}

void GameController::connect_tetrimino_with_board() {
  _tetrimino->set_parent(_board.get());
  _tetrimino->set_location({8, 0});
  _tetrimino->set_board(_board.get());
}