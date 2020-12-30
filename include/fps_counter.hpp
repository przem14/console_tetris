#pragma once

#include <chrono>
#include <deque>

class FpsCounter {
  using time_point = std::chrono::steady_clock::time_point;

public:
  void add(time_point time) {
    const auto should_remove_last = [this, time]() {
      using namespace std::chrono;
      return duration_cast<seconds>(time - _data.front()).count() > 0;
    };

    _data.push_back(time);
    while (!_data.empty() && should_remove_last()) {
      _data.pop_front();
    }
  }

  int value() const { return _data.size(); }

private:
  std::deque<time_point> _data;
};