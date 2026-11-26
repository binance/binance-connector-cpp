//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <functional>
#include <string_view>

#include <binance/common/export.hpp>

// X11 headers define `None` as a macro.
#pragma push_macro("None")
#undef None

namespace binance::common {

enum class LogLevel { Debug, Info, Warn, Error, None };

/// Process-wide logger. Defaults to `Info` on stderr, or to the level named by the
/// `LOG_LEVEL` environment variable (`debug`, `info`, `warn`, `error`, `none`).
class BINANCE_COMMON_EXPORT Logger {
public:
    using Sink = std::function<void(LogLevel, std::string_view)>;

    static void set_level(LogLevel level) noexcept;
    [[nodiscard]] static LogLevel level() noexcept;
    /// Replaces the output. An empty sink restores stderr. The sink may be called from any
    /// thread; exceptions it throws are discarded.
    static void set_sink(Sink sink);

    [[nodiscard]] static bool enabled(LogLevel level) noexcept { return level >= Logger::level(); }
    static void log(LogLevel level, std::string_view message) noexcept;

    static void debug(std::string_view message) noexcept { log(LogLevel::Debug, message); }
    static void info(std::string_view message) noexcept { log(LogLevel::Info, message); }
    static void warn(std::string_view message) noexcept { log(LogLevel::Warn, message); }
    static void error(std::string_view message) noexcept { log(LogLevel::Error, message); }
};

} // namespace binance::common

#pragma pop_macro("None")
