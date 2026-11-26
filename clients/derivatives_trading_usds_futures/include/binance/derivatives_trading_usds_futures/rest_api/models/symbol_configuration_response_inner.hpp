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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct SymbolConfigurationResponseInner {
    std::optional<std::string> symbol;
    std::optional<std::string> margin_type;
    std::optional<bool> is_auto_add_margin;
    std::optional<std::int64_t> leverage;
    std::optional<std::string> max_notional_value;

    bool operator==(const SymbolConfigurationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolConfigurationResponseInner
tag_invoke(boost::json::value_to_tag<SymbolConfigurationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolConfigurationResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
