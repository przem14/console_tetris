#include <Windows.h>

#include "console_screen.hpp"
#include "fps_counter.hpp"
#include "game_controller.hpp"
#include "label.hpp"
#include "screen_buffer.hpp"
#include "text_utils.hpp"
#include "vec2d.hpp"
#include <array>
#include <chrono>
#include <string>
#include <tchar.h>

int main() {
  ConsoleScreen screen{};
  ScreenBuffer buffer{static_cast<size_t>(screen.width()),
                      static_cast<size_t>(screen.height())};
  FpsCounter fps_counter{};

  auto prev_time = std::chrono::steady_clock::now();

  GameController game_controller{};
  ValueLabel fps_label{_TEXT("FPS=")};
  fps_label.set_location({0, screen.height() - 1});

  while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
    fps_counter.add(std::chrono::steady_clock::now());
    fps_label.set_value(fps_counter.value());

    const auto curr_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta_time = curr_time - prev_time;
    prev_time = curr_time;

    game_controller.update(delta_time.count());

    buffer.clear();
    game_controller.draw(buffer);
    fps_label.draw(buffer);

    screen.show(buffer.data(), buffer.size());
  }

  return 0;
}