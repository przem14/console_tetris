#pragma once

struct Vec2d {
  int x;
  int y;
};

Vec2d operator+(const Vec2d &lhs, const Vec2d &rhs);
Vec2d operator-(const Vec2d &lhs, const Vec2d &rhs);