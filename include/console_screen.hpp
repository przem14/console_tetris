#pragma once

#include <Windows.h>
#include <tchar.h>

class ConsoleScreen {
public:
  ConsoleScreen();

  void show(const _TCHAR *buffer, size_t buffer_size);

  SHORT width() const { return _width; }
  SHORT height() const { return _height; }

private:
  HANDLE _handle{0};
  SHORT _width{0};
  SHORT _height{0};
};