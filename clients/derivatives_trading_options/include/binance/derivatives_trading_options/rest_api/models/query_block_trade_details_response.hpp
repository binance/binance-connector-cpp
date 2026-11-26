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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_details_response_legs_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct QueryBlockTradeDetailsResponse {
    /// block Trade Settlement Key
    std::optional<std::string> block_trade_settlement_key;
    /// expire Time
    std::optional<std::int64_t> expire_time;
    /// liquidity
    std::optional<std::string> liquidity;
    /// status
    std::optional<std::string> status;
    /// create Time
    std::optional<std::int64_t> create_time;
    /// legs
    std::optional<std::vector<QueryBlockTradeDetailsResponseLegsInner>> legs;

    bool operator==(const QueryBlockTradeDetailsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT QueryBlockTradeDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryBlockTradeDetailsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const QueryBlockTradeDetailsResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
