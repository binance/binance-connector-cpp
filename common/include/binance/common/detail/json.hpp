//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/object.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_from.hpp>
#include <boost/json/value_to.hpp>

#include <binance/common/detail/utils.hpp>
#include <binance/common/models.hpp>
#include <binance/common/required.hpp>

/// Helpers used by the product models to map JSON objects to structs. Internal.
namespace binance::common::detail::json {

/// Sets `out` if `key` is present and not `null`.
///
/// Like the other `read` overloads, throws a `DecodeError` naming the field (and the element
/// within it) if the value does not match `T`.
template <class T>
void read(const boost::json::object& obj, std::string_view key, std::optional<T>& out) {
    if (const auto* v = obj.if_contains(key); v != nullptr && !v->is_null()) {
        out = decode_at<T>(*v, key);
    }
}

/// For nullable fields: unset if `key` is missing, set to `nullopt` if it is `null`.
template <class T>
void read(const boost::json::object& obj, std::string_view key,
          std::optional<std::optional<T>>& out) {
    if (const auto* v = obj.if_contains(key)) {
        out.emplace();
        if (!v->is_null()) {
            *out = decode_at<T>(*v, key);
        }
    }
}

/// Throws a `DecodeError` if `key` is missing.
template <class T> void read(const boost::json::object& obj, std::string_view key, T& out) {
    const auto* v = obj.if_contains(key);
    if (v == nullptr) {
        throw DecodeError(std::string(key), "missing required field");
    }
    out = decode_at<T>(*v, key);
}

template <class T>
void write(boost::json::object& obj, std::string_view key, const std::optional<T>& value) {
    if (value) {
        obj[key] = boost::json::value_from(*value);
    }
}

/// Writes `null` for a set but empty nullable field.
template <class T>
void write(boost::json::object& obj, std::string_view key,
           const std::optional<std::optional<T>>& value) {
    if (!value) {
        return;
    }
    if (*value) {
        obj[key] = boost::json::value_from(**value);
    } else {
        obj[key] = nullptr;
    }
}

template <class T> void write(boost::json::object& obj, std::string_view key, const T& value) {
    obj[key] = boost::json::value_from(value);
}

/// Adds a request parameter, converted with `boost::json::value_from` (so `Decimal` and
/// enums become strings).
template <class T> void set_param(Params& params, const std::string& key, const T& value) {
    params[key] = boost::json::value_from(value);
}

template <class T>
void set_param(Params& params, const std::string& key, const Required<T>& value) {
    params[key] = boost::json::value_from(*value);
}

/// Adds the parameter only if it is set.
template <class T>
void set_param(Params& params, const std::string& key, const std::optional<T>& value) {
    if (value) {
        params[key] = boost::json::value_from(*value);
    }
}

/// The text of a header or path parameter: strings as they are, anything else as compact JSON
/// with doubles in plain notation (see `detail::to_json_string`).
inline std::string param_text(const boost::json::value& value) {
    return param_to_string(value);
}

/// Percent-encodes everything but the RFC 3986 unreserved characters.
inline std::string percent_encode(std::string_view text) {
    constexpr std::string_view kHex = "0123456789ABCDEF";
    std::string out;
    out.reserve(text.size());
    for (const char c : text) {
        const auto byte = static_cast<unsigned char>(c);
        if ((byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z') ||
            (byte >= '0' && byte <= '9') || c == '-' || c == '.' || c == '_' || c == '~') {
            out += c;
        } else {
            out += '%';
            out += kHex[byte >> 4U];
            out += kHex[byte & 0x0FU];
        }
    }
    return out;
}

// The result is used within the caller's expression, while the argument still exists.
template <class T> const T& param_value(const T& value) {
    return value; // NOLINT(bugprone-return-const-ref-from-parameter)
}
template <class T> const T& param_value(const Required<T>& value) {
    return *value;
}

/// Replaces `{key}` in `endpoint` with the percent-encoded value.
template <class T>
void set_path_param(std::string& endpoint, std::string_view key, const T& value) {
    const auto placeholder = "{" + std::string(key) + "}";
    const auto text = percent_encode(param_text(boost::json::value_from(param_value(value))));
    for (auto pos = endpoint.find(placeholder); pos != std::string::npos;
         pos = endpoint.find(placeholder, pos + text.size())) {
        endpoint.replace(pos, placeholder.size(), text);
    }
}

/// Adds a request header.
template <class T>
void set_header(std::vector<std::pair<std::string, std::string>>& headers, std::string key,
                const T& value) {
    headers.emplace_back(std::move(key), param_text(boost::json::value_from(param_value(value))));
}

/// Adds the header only if it is set.
template <class T>
void set_header(std::vector<std::pair<std::string, std::string>>& headers, std::string key,
                const std::optional<T>& value) {
    if (value) {
        set_header(headers, std::move(key), *value);
    }
}

/// The object behind `jv`, or a `DecodeError` naming the model being decoded.
inline const boost::json::object& as_object(const boost::json::value& jv, std::string_view model) {
    const auto* obj = jv.if_object();
    if (obj == nullptr) {
        throw DecodeError({}, "expected a JSON object for " + std::string(model));
    }
    return *obj;
}

} // namespace binance::common::detail::json
