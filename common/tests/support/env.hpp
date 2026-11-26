//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdlib>
#include <mutex>
#include <optional>
#include <string>

namespace binance::test {

/// Recursive so that one test can hold several guards.
inline std::recursive_mutex& env_mutex() {
    static std::recursive_mutex m;
    return m;
}

/// Sets an environment variable for the lifetime of the guard, restoring the old value.
class ScopedEnv {
public:
    ScopedEnv(std::string name, const std::optional<std::string>& value)
        : lock_(env_mutex()), name_(std::move(name)) {
        if (const char* old = std::getenv(name_.c_str())) {
            old_ = old;
        }
        set(value);
    }
    ~ScopedEnv() { set(old_); }
    ScopedEnv(const ScopedEnv&) = delete;
    ScopedEnv& operator=(const ScopedEnv&) = delete;

private:
    void set(const std::optional<std::string>& value) {
#if defined(_WIN32)
        _putenv_s(name_.c_str(), value ? value->c_str() : "");
#else
        if (value) {
            ::setenv(name_.c_str(), value->c_str(), 1);
        } else {
            ::unsetenv(name_.c_str());
        }
#endif
    }

    std::lock_guard<std::recursive_mutex> lock_;
    std::string name_;
    std::optional<std::string> old_;
};

} // namespace binance::test
