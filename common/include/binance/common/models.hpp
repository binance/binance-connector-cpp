//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <exception>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include <boost/json/conversion.hpp>
#include <boost/json/parse.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_to.hpp>
#include <boost/system/system_error.hpp>

#include <binance/common/errors.hpp>
#include <binance/common/export.hpp>

namespace binance::common {

enum class TimeUnit { Millisecond, Microsecond };

[[nodiscard]] constexpr std::string_view to_upper_string(TimeUnit unit) noexcept {
    return unit == TimeUnit::Millisecond ? "MILLISECOND" : "MICROSECOND";
}

[[nodiscard]] constexpr std::string_view to_lower_string(TimeUnit unit) noexcept {
    return unit == TimeUnit::Millisecond ? "millisecond" : "microsecond";
}

enum class RateLimitType { RequestWeight, Orders, RawRequests };

enum class Interval { Second, Minute, Hour, Day };

/// `REQUEST_WEIGHT`, `ORDERS`, `RAW_REQUESTS`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string_view to_string(RateLimitType type) noexcept;
/// `SECOND`, `MINUTE`, `HOUR`, `DAY`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string_view to_string(Interval interval) noexcept;

struct RestApiRateLimit {
    RateLimitType rate_limit_type = RateLimitType::RequestWeight;
    Interval interval = Interval::Minute;
    std::uint32_t interval_num = 0;
    std::uint32_t count = 0;
    std::optional<std::uint32_t> retry_after;

    friend bool operator==(const RestApiRateLimit&, const RestApiRateLimit&) = default;
};

/// `{"rateLimitType", "interval", "intervalNum", "count", "retryAfter"}`, for logging.
BINANCE_COMMON_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const RestApiRateLimit& limit);

/// Response headers, keyed by lower-cased header name.
using Headers = std::map<std::string, std::string>;

/// Request parameters, sorted by name. `null` values are skipped when serialised.
using Params = std::map<std::string, boost::json::value>;

/// An undecoded REST response.
struct RawResponse {
    std::uint16_t status = 0;
    // The empty initializers keep GCC's -Wmissing-field-initializers quiet for designated
    // initializers that leave these members out.
    Headers headers{};
    std::optional<std::vector<RestApiRateLimit>> rate_limits{};
    std::string body;
};

/// Parses JSON keeping 64-bit integers and long decimals exact.
/// Throws `ConnectorClientError` on malformed input.
[[nodiscard]] BINANCE_COMMON_EXPORT boost::json::value parse_json(std::string_view text);

namespace detail {

/// A JSON value that does not match the type it is decoded into. `what()` is
/// `"field '<path>': <reason>"`, e.g. `field 'symbols[2].price': Invalid decimal: 'abc'`, or just
/// the reason when the top-level value is at fault.
class DecodeError : public std::invalid_argument {
public:
    DecodeError(std::string path, std::string reason)
        : std::invalid_argument(path.empty() ? reason : "field '" + path + "': " + reason),
          path_(std::move(path)), reason_(std::move(reason)) {}

    [[nodiscard]] const std::string& path() const noexcept { return path_; }
    [[nodiscard]] const std::string& reason() const noexcept { return reason_; }

    /// The same error, one level up: `segment` is a field name or an `[index]`.
    [[nodiscard]] DecodeError within(std::string_view segment) const {
        std::string path(segment);
        if (!path_.empty()) {
            if (!path_.starts_with('[')) {
                path += '.';
            }
            path += path_;
        }
        return {std::move(path), reason_};
    }

private:
    std::string path_;
    std::string reason_;
};

template <class T> struct IsVector : std::false_type {};
template <class T, class A> struct IsVector<std::vector<T, A>> : std::true_type {};
template <class T> struct IsStringMap : std::false_type {};
template <class T, class C, class A>
struct IsStringMap<std::map<std::string, T, C, A>> : std::true_type {};
template <class T> struct IsOptional : std::false_type {};
template <class T> struct IsOptional<std::optional<T>> : std::true_type {};

template <class T> struct IsJsonVariant : std::false_type {};
/// The result of a `oneOf` of the WebSocket API: its alternatives, then the raw JSON.
template <class... Ts>
struct IsJsonVariant<std::variant<Ts...>>
    : std::bool_constant<(std::is_same_v<Ts, boost::json::value> || ...)> {};

template <class T> T decode(const boost::json::value& jv);

/// Whether `jv` has the JSON kind of `T` (models are objects).
template <class T> [[nodiscard]] bool has_kind_of(const boost::json::value& jv) noexcept {
    if constexpr (IsOptional<T>::value) {
        return jv.is_null() || has_kind_of<typename T::value_type>(jv);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return jv.is_string();
    } else if constexpr (std::is_same_v<T, bool>) {
        return jv.is_bool();
    } else if constexpr (std::is_integral_v<T>) {
        return jv.is_int64() || jv.is_uint64();
    } else if constexpr (std::is_floating_point_v<T>) {
        return jv.is_number();
    } else if constexpr (IsVector<T>::value) {
        return jv.is_array();
    } else {
        return jv.is_object();
    }
}

/// The first alternative that decodes `jv`. Only when `jv` has the kind of none of them is it
/// kept as raw JSON: a value that has the right kind but does not decode is an error, as it is
/// for any other model.
template <class V, std::size_t... I>
V decode_variant(const boost::json::value& jv, std::index_sequence<I...> /*unused*/) {
    std::optional<V> out;
    std::exception_ptr failure;
    const auto attempt = [&]<std::size_t N>(std::integral_constant<std::size_t, N> /*unused*/) {
        using A = std::variant_alternative_t<N, V>;
        if constexpr (!std::is_same_v<A, boost::json::value>) {
            if (out || !has_kind_of<A>(jv)) {
                return;
            }
            try {
                out.emplace(std::in_place_index<N>, decode<A>(jv));
            } catch (const std::bad_alloc&) {
                throw;
            } catch (const std::exception&) {
                if (!failure) {
                    failure = std::current_exception();
                }
            }
        }
    };
    (attempt(std::integral_constant<std::size_t, I>{}), ...);
    if (out) {
        return std::move(*out);
    }
    if (failure) {
        std::rethrow_exception(failure);
    }
    return V(std::in_place_type<boost::json::value>, jv);
}

/// Runs `decode` for the element at `segment`, rethrowing any failure as a `DecodeError` there.
template <class T> T decode_at(const boost::json::value& jv, std::string_view segment) {
    try {
        return decode<T>(jv);
    } catch (const DecodeError& e) {
        throw e.within(segment);
    } catch (const std::bad_alloc&) {
        throw;
    } catch (const std::exception& e) {
        throw DecodeError(std::string(segment), e.what());
    }
}

/// `boost::json::value_to<T>`, except that vectors, string-keyed maps and optionals are
/// decoded element by element, so a failure keeps its own message and is located by a
/// `DecodeError` (Boost reports a nested failure as a bare "got exception"). Boost's own errors
/// carry only their message, without source location.
template <class T> T decode(const boost::json::value& jv) {
    if constexpr (IsVector<T>::value) {
        const auto* array = jv.if_array();
        if (array == nullptr) {
            throw DecodeError({}, "expected a JSON array");
        }
        T out;
        out.reserve(array->size());
        for (std::size_t i = 0; i < array->size(); ++i) {
            out.push_back(
                decode_at<typename T::value_type>((*array)[i], "[" + std::to_string(i) + "]"));
        }
        return out;
    } else if constexpr (IsStringMap<T>::value) {
        const auto* object = jv.if_object();
        if (object == nullptr) {
            throw DecodeError({}, "expected a JSON object");
        }
        T out;
        for (const auto& [key, item] : *object) {
            out.emplace(std::string(key), decode_at<typename T::mapped_type>(item, key));
        }
        return out;
    } else if constexpr (IsOptional<T>::value) {
        if (jv.is_null()) {
            return T{};
        }
        return T{decode<typename T::value_type>(jv)};
    } else if constexpr (IsJsonVariant<T>::value) {
        return decode_variant<T>(jv, std::make_index_sequence<std::variant_size_v<T>>{});
    } else {
        try {
            return boost::json::value_to<T>(jv);
        } catch (const boost::system::system_error& e) {
            throw DecodeError({}, e.code().message());
        }
    }
}

/// The decoded value of a response, computed once and shared by its copies (moved-from ones
/// included). A decode that throws is retried on the next call.
template <class T> class DecodeCache {
public:
    DecodeCache() = default;
    DecodeCache(const DecodeCache&) = default;
    DecodeCache& operator=(const DecodeCache&) = default;
    // Copies on purpose: a moved-from response still shares the decoded value.
    // NOLINTNEXTLINE(performance-move-constructor-init)
    DecodeCache(DecodeCache&& other) noexcept : state_(other.state_) {}
    DecodeCache& operator=(DecodeCache&& other) noexcept {
        state_ = other.state_;
        return *this;
    }
    ~DecodeCache() = default;

    template <class F> const T& get(F&& decode) const {
        const std::lock_guard lock(state_->mutex);
        if (!state_->value) {
            state_->value.emplace(decode());
        }
        return *state_->value;
    }

private:
    struct State {
        std::mutex mutex;
        std::optional<T> value;
    };
    std::shared_ptr<State> state_ = std::make_shared<State>();
};

} // namespace detail

/// A successful REST response whose body is decoded into `T` on first use.
///
/// `T` must be convertible with `boost::json::value_to<T>`, through a `tag_invoke` overload
/// that the product models provide.
template <class T> class RestApiResponse {
public:
    RestApiResponse() = default;
    explicit RestApiResponse(RawResponse raw) : raw_(std::move(raw)) {}

    /// The decoded body, decoded on the first call. Throws `ConnectorClientError` if it is not
    /// valid JSON or does not match `T`.
    [[nodiscard]] const T& data() const {
        return cache_.get([this] {
            auto jv = parse_json(raw_.body);
            try {
                return detail::decode<T>(jv);
            } catch (const std::exception& e) {
                throw ConnectorClientError(std::string("Failed to decode response: ") + e.what());
            }
        });
    }

    [[nodiscard]] std::uint16_t status() const noexcept { return raw_.status; }
    [[nodiscard]] const Headers& headers() const noexcept { return raw_.headers; }
    [[nodiscard]] const std::optional<std::vector<RestApiRateLimit>>& rate_limits() const noexcept {
        return raw_.rate_limits;
    }
    /// The undecoded response body.
    [[nodiscard]] const std::string& body() const noexcept { return raw_.body; }
    [[nodiscard]] const RawResponse& raw() const noexcept { return raw_; }

private:
    RawResponse raw_;
    detail::DecodeCache<T> cache_;
};

/// How many connections a WebSocket client keeps open. Requests and subscriptions are spread
/// over them round-robin.
class WebsocketMode {
public:
    constexpr WebsocketMode() noexcept = default;

    [[nodiscard]] static constexpr WebsocketMode single() noexcept { return {}; }
    /// `size` connections. 0 is treated as 1.
    [[nodiscard]] static constexpr WebsocketMode pool(std::size_t size) noexcept {
        return {size == 0 ? 1 : size, true};
    }

    [[nodiscard]] constexpr std::size_t pool_size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool is_pool() const noexcept { return pool_; }

    friend constexpr bool operator==(const WebsocketMode&, const WebsocketMode&) = default;

private:
    constexpr WebsocketMode(std::size_t size, bool pool) noexcept : size_(size), pool_(pool) {}

    std::size_t size_ = 1;
    bool pool_ = false;
};

/// An entry of a WebSocket API response's `rateLimits`.
struct WebsocketApiRateLimit {
    RateLimitType rate_limit_type = RateLimitType::RequestWeight;
    Interval interval = Interval::Minute;
    std::uint32_t interval_num = 0;
    std::uint32_t limit = 0;
    std::uint32_t count = 0;

    friend bool operator==(const WebsocketApiRateLimit&, const WebsocketApiRateLimit&) = default;
};

/// `{"rateLimitType", "interval", "intervalNum", "limit", "count"}`, for logging.
BINANCE_COMMON_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const WebsocketApiRateLimit& limit);

/// How a WebSocket API request is authenticated.
struct WebsocketMessageSendOptions {
    /// Adds `apiKey`.
    bool with_api_key = false;
    /// Adds `apiKey`, `timestamp` and `signature`.
    bool is_signed = false;
    /// `session.logon`: sent on every connection, and remembered for re-logon.
    bool is_session_logon = false;
    /// `session.logout`: sent on every connection.
    bool is_session_logout = false;
};

/// A SUBSCRIBE / UNSUBSCRIBE request id: a 32-character hex string or a number.
using StreamId = std::variant<std::string, std::uint32_t>;

/// A successful WebSocket API response, before decoding.
struct WebsocketApiRawResponse {
    /// The response's `result` (or `response`) member.
    boost::json::value result;
    std::optional<std::vector<WebsocketApiRateLimit>> rate_limits;
};

/// A successful WebSocket API response whose `result` is decoded into `T` on first use.
template <class T> class WebsocketApiResponse {
public:
    WebsocketApiResponse() = default;
    explicit WebsocketApiResponse(WebsocketApiRawResponse raw) : raw_(std::move(raw)) {}

    /// The decoded `result`, decoded on the first call. Throws `ConnectorClientError` if it does
    /// not match `T`.
    [[nodiscard]] const T& data() const {
        return cache_.get([this] {
            try {
                return detail::decode<T>(raw_.result);
            } catch (const std::exception& e) {
                throw ConnectorClientError(std::string("Failed to decode response: ") + e.what());
            }
        });
    }

    [[nodiscard]] const std::optional<std::vector<WebsocketApiRateLimit>>&
    rate_limits() const noexcept {
        return raw_.rate_limits;
    }
    [[nodiscard]] const WebsocketApiRawResponse& raw() const noexcept { return raw_; }

private:
    WebsocketApiRawResponse raw_;
    detail::DecodeCache<T> cache_;
};

} // namespace binance::common
