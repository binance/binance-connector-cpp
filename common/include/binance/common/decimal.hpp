//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <compare>
#include <concepts>
#include <ostream>
#include <string>
#include <string_view>

#include <boost/json/fwd.hpp>
#include <boost/json/value_from.hpp>
#include <boost/json/value_to.hpp>

#include <binance/common/export.hpp>

namespace binance::common {

namespace detail {
template <class T>
concept BoolOrCharacter =
    std::same_as<T, bool> || std::same_as<T, char> || std::same_as<T, wchar_t> ||
    std::same_as<T, char8_t> || std::same_as<T, char16_t> || std::same_as<T, char32_t>;
} // namespace detail

/// Exact decimal number, stored as its canonical plain-notation string.
///
/// Canonical form: optional `-`, digits, optional `.` and digits. Leading zeros of the integer
/// part, trailing zeros of the fraction and `-0` are normalised away
/// (`"0010.500"` → `"10.5"`).
///
/// Exactness is guaranteed for text and integer inputs only. A `double` already carries binary
/// rounding, so `Decimal(double)` keeps the shortest text that round-trips it, not the exact
/// value the double was meant to hold.
class BINANCE_COMMON_EXPORT Decimal {
public:
    Decimal() = default;

    /// Parses `"123"`, `"-0.001"`, `"1.5e-7"`, …; throws `std::invalid_argument` otherwise.
    explicit Decimal(std::string_view text);
    /// Throws `std::invalid_argument` for a null pointer.
    explicit Decimal(const char* text);
    explicit Decimal(const std::string& text) : Decimal(std::string_view(text)) {}

    /// Shortest representation that round-trips the double (`0.1` → `"0.1"`).
    /// Throws `std::invalid_argument` for NaN / infinity.
    explicit Decimal(double value);
    /// Rejected: a `float` widens to a double that is not the value it was written as
    /// (`0.1f` → `0.100000001490116`). Pass a string, or cast to `double` explicitly.
    template <std::same_as<float> T> Decimal(T) = delete;

    template <std::integral T>
        requires(!detail::BoolOrCharacter<T>)
    explicit Decimal(T value) : repr_(std::to_string(value)) {}
    /// `bool` and character types are rejected.
    template <detail::BoolOrCharacter T> Decimal(T) = delete;

    Decimal(const Decimal&) = default;
    Decimal& operator=(const Decimal&) = default;
    /// A moved-from `Decimal` is zero (still canonical).
    // "0" fits the small-string buffer: these never allocate.
    // NOLINTBEGIN(bugprone-exception-escape)
    Decimal(Decimal&& other) noexcept { repr_.swap(other.repr_); }
    Decimal& operator=(Decimal&& other) noexcept {
        if (this != &other) {
            repr_.swap(other.repr_);
            other.repr_.assign(1, '0');
        }
        return *this;
    }
    // NOLINTEND(bugprone-exception-escape)
    ~Decimal() = default;

    [[nodiscard]] const std::string& str() const noexcept { return repr_; }
    /// The nearest double; values beyond its range become `±HUGE_VAL` or `±0.0`.
    [[nodiscard]] double to_double() const;

    /// Numeric comparison. Equality is exact because the representation is canonical.
    friend bool operator==(const Decimal& a, const Decimal& b) noexcept = default;
    friend BINANCE_COMMON_EXPORT std::strong_ordering operator<=>(const Decimal& a,
                                                                  const Decimal& b) noexcept;

private:
    std::string repr_ = "0";
};

inline std::ostream& operator<<(std::ostream& os, const Decimal& d) {
    return os << d.str();
}

/// Serialised as a JSON string.
BINANCE_COMMON_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const Decimal& d);
/// Accepts a JSON string or number.
///
/// A JSON string is converted exactly. A JSON number is exact if it is an integer that fits in
/// 64 bits; any other number is parsed as a double first (see `Decimal(double)`), so digits beyond
/// double precision are lost (`0.12345678901234567890` → `"0.12345678901234568"`). Binance sends
/// prices and quantities as strings.
BINANCE_COMMON_EXPORT Decimal tag_invoke(boost::json::value_to_tag<Decimal> /*tag*/,
                                         const boost::json::value& jv);

} // namespace binance::common
