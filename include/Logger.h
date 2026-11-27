#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <utility>

class Logger final {
public:
  template <typename... Args>
  static void Info(Args &&...args) {
    Write(std::clog, "INFO", std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Error(Args &&...args) {
    Write(std::cerr, "ERROR", std::forward<Args>(args)...);
  }

private:
  template <typename... Args>
  static void Write(std::ostream &output, const char *level, Args &&...args) {
    const std::lock_guard<std::mutex> lock(mutex);

    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    const auto milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) %
        1000;

    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream message;
    (message << ... << std::forward<Args>(args));

    std::ostringstream timestamp;
    timestamp << '[' << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << '.'
              << std::setfill('0') << std::setw(3) << milliseconds.count()
              << ']';
    output << timestamp.str() << " [" << level << "] " << message.str()
           << '\n';
  }

  static std::mutex mutex;
};
