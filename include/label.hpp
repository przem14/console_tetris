#pragma once

#include "entity.hpp"
#include "screen_buffer.hpp"
#include "text_utils.hpp"

class Label : public Entity {
public:
  Label(const _TCHAR *text) : _text(text) {}

  void draw(ScreenBuffer &buffer) const override {
    const auto p = location();
    buffer.write(p.x, p.y, _text.data());
  }

private:
  tstring _text;
};

class ValueLabel : public Entity {
public:
  ValueLabel(const _TCHAR *text) : _text(text) {}

  void set_value(int value) { _value = value; }
  int value() const { return _value; }

  void draw(ScreenBuffer &buffer) const override {
    const auto p = location();
    buffer.write(p.x, p.y, _text.data());
    buffer.write(p.x + _text.length(), p.y, TO_STR(_value).data());
  }

private:
  tstring _text;
  int _value{0};
};