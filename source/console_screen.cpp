#include "console_screen.hpp"

ConsoleScreen::ConsoleScreen() {
  _handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                      CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(_handle);

  CONSOLE_SCREEN_BUFFER_INFO console_info;
  GetConsoleScreenBufferInfo(_handle, &console_info);
  _width = console_info.dwSize.X;
  _height = console_info.dwSize.Y;
}

void ConsoleScreen::show(const _TCHAR *buffer, size_t buffer_size) {
  DWORD dwBytesWritten = 0;
  WriteConsoleOutputCharacter(_handle, buffer, buffer_size, {0, 0},
                              &dwBytesWritten);
}