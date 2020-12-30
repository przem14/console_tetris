#include "screen_buffer.hpp"

ScreenBuffer::ScreenBuffer(size_t width, size_t height) {
  _buffer = std::vector<_TCHAR>(width * height + 1);
  _width = width;
  clear();
}

void ScreenBuffer::clear() {
  for (auto &c : _buffer) {
    c = Chars::SPACE;
  }
}

void ScreenBuffer::write(size_t x, size_t y, _TCHAR c) {
  _buffer[y * _width + x] = c;
}

void ScreenBuffer::write(size_t x, size_t y, const _TCHAR *c) {
  size_t i = 0;
  size_t start = y * _width + x;
  while (*(c + i) != '\0') {
    _buffer[start + i] = *(c + i);
    ++i;
  }
}