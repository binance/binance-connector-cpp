//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string>

#include <boost/json/serialize.hpp>
#include <boost/json/value_from.hpp>

namespace binance::common {

/// The JSON text of a value of the SDK: a model, a response's `data()` or `rate_limits()`, a
/// stream event, a `Decimal`, or a container of them (anything `boost::json::value_from`
/// converts), e.g. `common::to_json(response.data())`. Prices and quantities stay strings, so
/// nothing is rounded.
template <class T> [[nodiscard]] std::string to_json(const T& value) {
    return boost::json::serialize(boost::json::value_from(value));
}

} // namespace binance::common
