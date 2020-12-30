#include "vec2d.hpp"

Vec2d operator+(const Vec2d &lhs, const Vec2d &rhs) {
  return Vec2d{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2d operator-(const Vec2d &lhs, const Vec2d &rhs) {
  return Vec2d{lhs.x - rhs.x, lhs.y - rhs.y};
}