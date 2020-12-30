#include "tetrimino.hpp"

Tetrimino::Tetrimino(std::vector<Vec2d> points) : _points(points) {}

std::unique_ptr<Tetrimino> Tetrimino::create(char type) {
  std::vector<Vec2d> points{};
  switch (type) {
  case 'T':
    points = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
    break;
  case 'I':
    points = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
    break;
  case 'O':
    points = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    break;
  case 'L':
    points = {{0, 0}, {0, 1}, {0, 2}, {1, 2}};
    break;
  case 'J':
    points = {{1, 0}, {1, 1}, {0, 2}, {1, 2}};
    break;
  case 'S':
    points = {{1, 0}, {2, 0}, {0, 1}, {1, 1}};
    break;
  case 'Z':
    points = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
  }
  return std::make_unique<Tetrimino>(points);
}

void Tetrimino::draw(ScreenBuffer &buffer) const {
  for (auto p : points_to_draw()) {
    p = p + world_location();
    buffer.write(p.x, p.y, Chars::BLOCK);
  }
}

void Tetrimino::update(double delta_seconds) {
  const int current_level = location().y;
  if (GetAsyncKeyState('A') & 0x8000) {
    if (!is_pressed && !is_blocked({-2, 0})) {
      set_location(location() + Vec2d{-2, 0});
    }
    is_pressed = true;
  } else if (GetAsyncKeyState('D') & 0x8000) {
    if (!is_pressed && !is_blocked({2, 0})) {
      set_location(location() + Vec2d{2, 0});
    }
    is_pressed = true;
  } else if (GetAsyncKeyState('S') & 0x8000) {
    while (!is_pressed && !is_blocked({0, 1})) {
      set_location(location() + Vec2d{0, 1});
      _fall_delay = 2.0;
    }
    is_pressed = true;
  } else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
    if (!is_pressed) {
      rotate();
    }
    is_pressed = true;
  } else {
    is_pressed = false;
  }

  _fall_delay += delta_seconds;
  if (_fall_delay > 1.0) {
    if (is_blocked({0, 1})) {
      _board->insert(points_to_draw(), location(), current_level);
    } else {
      set_location(location() + Vec2d{0, 1});
    }
    _fall_delay = 0.0;
  }
}

bool Tetrimino::is_blocked(const Vec2d &dir) const {
  if (_board == nullptr) {
    return false;
  }
  const auto points = points_to_draw();
  return std::any_of(points.begin(), points.end(), [this, &dir](const auto &p) {
    return _board->is_blocked(p + location() + dir);
  });
}

std::vector<Vec2d> Tetrimino::points_to_draw() const {
  std::vector<Vec2d> res;
  for (const auto &p : _points) {
    res.push_back({p.x * 2, p.y});
    res.push_back({p.x * 2 + 1, p.y});
  }
  return res;
}

void Tetrimino::rotate() {
  auto prev = _points;
  for (auto &p : _points) {
    p = Vec2d{p.y, -p.x + 2};
  }
  if (is_blocked({0, 0})) {
    _points.swap(prev);
  }
}