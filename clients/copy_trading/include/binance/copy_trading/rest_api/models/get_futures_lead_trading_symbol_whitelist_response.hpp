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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/copy_trading/export.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trading_symbol_whitelist_response_data_inner.hpp>

namespace binance::copy_trading::rest_api {

struct GetFuturesLeadTradingSymbolWhitelistResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Whitelisted symbols for futures lead trading
    std::optional<std::vector<GetFuturesLeadTradingSymbolWhitelistResponseDataInner>> data;

    bool operator==(const GetFuturesLeadTradingSymbolWhitelistResponse& /*other*/) const = default;
};

BINANCE_COPY_TRADING_EXPORT GetFuturesLeadTradingSymbolWhitelistResponse
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTradingSymbolWhitelistResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_COPY_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                            boost::json::value& jv,
                                            const GetFuturesLeadTradingSymbolWhitelistResponse& v);

} // namespace binance::copy_trading::rest_api
