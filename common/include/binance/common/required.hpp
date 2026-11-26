//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <concepts>
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace binance::common {

namespace detail {
struct NotAList {};
template <class T> struct ListElement {
    using type = NotAList;
};
template <class T>
    requires requires { typename T::value_type; }
struct ListElement<T> {
    using type = typename T::value_type;
};
} // namespace detail

/// A request parameter that must be set. It has no default value, so leaving it out of a
/// designated initializer is a compile error:
///
///     NewOrderParams params{.symbol = "BNBUSDT", .side = NewOrderSideEnum::Buy,
///                           .type = NewOrderTypeEnum::Market};
///
/// It converts implicitly to `const T&`; use `*` or `->` to reach the value directly.
template <class T> class Required {
    using Element = typename detail::ListElement<T>::type;

public:
    Required() = delete;
    Required(T value) noexcept(std::is_nothrow_move_constructible_v<T>)
        : value_(std::move(value)) {}
    template <class U>
        requires(!std::same_as<std::remove_cvref_t<U>, Required> &&
                 !std::same_as<std::remove_cvref_t<U>, T> && std::convertible_to<U, T>)
    Required(U&& value) : value_(std::forward<U>(value)) {}
    Required(std::initializer_list<Element> values)
        requires std::constructible_from<T, std::initializer_list<Element>>
        : value_(values) {}

    [[nodiscard]] const T& operator*() const& noexcept { return value_; }
    [[nodiscard]] T& operator*() & noexcept { return value_; }
    [[nodiscard]] T&& operator*() && noexcept { return std::move(value_); }
    [[nodiscard]] const T* operator->() const noexcept { return &value_; }
    [[nodiscard]] T* operator->() noexcept { return &value_; }
    operator const T&() const noexcept { return value_; }

    friend bool operator==(const Required& a, const Required& b)
        requires std::equality_comparable<T>
    {
        return a.value_ == b.value_;
    }

private:
    T value_;
};

} // namespace binance::common
