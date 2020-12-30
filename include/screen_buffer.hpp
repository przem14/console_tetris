#pragma once

#include "text_utils.hpp"
#include <vector>

class ScreenBuffer {
public:
  ScreenBuffer(size_t width, size_t height);

  size_t size() const { return _buffer.size(); }

  const _TCHAR *data() const { return _buffer.data(); }

  void clear();
  void write(size_t x, size_t y, _TCHAR c);
  void write(size_t x, size_t y, const _TCHAR *c);

private:
  std::vector<_TCHAR> _buffer;
  size_t _width{0};
};
