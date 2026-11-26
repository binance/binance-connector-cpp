//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountNewOtoResponseOrdersInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// client Order Id.
    std::optional<std::string> client_order_id;

    bool operator==(const MarginAccountNewOtoResponseOrdersInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoResponseOrdersInner
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoResponseOrdersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const MarginAccountNewOtoResponseOrdersInner& v);

} // namespace binance::margin_trading::rest_api
