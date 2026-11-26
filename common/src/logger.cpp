//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <mutex>
#include <string>

#include <binance/common/logger.hpp>

namespace binance::common {

namespace {

/// `LOG_LEVEL` (debug, info, warn, error, none; any case), `info` by default.
LogLevel initial_level() {
    const char* raw = std::getenv("LOG_LEVEL"); // NOLINT(concurrency-mt-unsafe)
    if (raw == nullptr) {
        return LogLevel::Info;
    }
    std::string value(raw);
    // ASCII-only: `std::tolower` depends on the C locale.
    std::transform(value.begin(), value.end(), value.begin(), [](char c) {
        return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c;
    });
    if (value == "debug") {
        return LogLevel::Debug;
    }
    if (value == "warn") {
        return LogLevel::Warn;
    }
    if (value == "error") {
        return LogLevel::Error;
    }
    if (value == "none" || value == "off") {
        return LogLevel::None;
    }
    return LogLevel::Info;
}

std::atomic<LogLevel>& level_ref() {
    static std::atomic<LogLevel> level{initial_level()};
    return level;
}

struct SinkState {
    std::mutex mutex;
    std::shared_ptr<const Logger::Sink> sink;
};

SinkState& sink_state() {
    // Leaked on purpose: logging from other static destructors must still find it.
    static auto* const state = new SinkState; // NOLINT(cppcoreguidelines-owning-memory)
    return *state;
}

std::string_view level_name(LogLevel level) {
    switch (level) {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warn:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    case LogLevel::None:
        break;
    }
    return "";
}

void stderr_sink(LogLevel level, std::string_view message) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm{};
#if defined(_WIN32)
    gmtime_s(&tm, &now);
#else
    gmtime_r(&now, &tm);
#endif
    std::array<char, 32> stamp{};
    std::strftime(stamp.data(), stamp.size(), "%Y-%m-%dT%H:%M:%SZ", &tm);
    const auto name = level_name(level);
    std::fprintf(stderr, "[%s] [binance] [%.*s] %.*s\n", stamp.data(),
                 static_cast<int>(name.size()), name.data(), static_cast<int>(message.size()),
                 message.data());
}

} // namespace

void Logger::set_level(LogLevel level) noexcept {
    level_ref().store(level);
}

LogLevel Logger::level() noexcept {
    return level_ref().load();
}

void Logger::set_sink(Sink sink) {
    auto& state = sink_state();
    std::lock_guard lock(state.mutex);
    state.sink = sink ? std::make_shared<const Sink>(std::move(sink)) : nullptr;
}

void Logger::log(LogLevel level, std::string_view message) noexcept {
    if (level == LogLevel::None || !enabled(level)) {
        return;
    }
    std::shared_ptr<const Sink> sink;
    {
        auto& state = sink_state();
        std::lock_guard lock(state.mutex);
        sink = state.sink;
    }
    // Logging is called from destructors and the I/O thread: a throwing sink must not escape.
    try {
        if (sink) {
            (*sink)(level, message);
        } else {
            stderr_sink(level, message);
        }
    } catch (...) { // NOLINT(bugprone-empty-catch): nowhere left to report a failing sink
    }
}

} // namespace binance::common
