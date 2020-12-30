#pragma once

#include "screen_buffer.hpp"
#include "vec2d.hpp"

class Entity {
public:
  virtual void draw(ScreenBuffer &buffer) const {}

  virtual void update(double delta_seconds) {}

  void set_location(Vec2d p) { _location = p; }
  Vec2d location() const { return _location; }
  Vec2d world_location() const {
    if (!_parent) {
      return _location;
    }
    return _location + _parent->location();
  }

  void set_parent(const Entity *parent) { _parent = parent; }

private:
  const Entity *_parent = nullptr;
  Vec2d _location{0, 0};
};
