//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/copy_trading/export.hpp>

namespace binance::copy_trading::rest_api {

struct GetFuturesLeadTradingSymbolWhitelistResponseDataInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Base asset
    std::optional<std::string> base_asset;
    /// Quote asset
    std::optional<std::string> quote_asset;

    bool operator==(const GetFuturesLeadTradingSymbolWhitelistResponseDataInner& /*other*/) const =
        default;
};

BINANCE_COPY_TRADING_EXPORT GetFuturesLeadTradingSymbolWhitelistResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTradingSymbolWhitelistResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_COPY_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFuturesLeadTradingSymbolWhitelistResponseDataInner& v);

} // namespace binance::copy_trading::rest_api
