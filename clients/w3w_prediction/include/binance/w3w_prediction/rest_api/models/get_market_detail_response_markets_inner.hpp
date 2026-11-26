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

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner_outcomes_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetMarketDetailResponseMarketsInner {
    std::optional<std::int64_t> market_id;
    std::optional<std::string> external_id;
    std::optional<std::string> title;
    std::optional<std::string> question;
    std::optional<std::string> description;
    std::optional<std::string> condition_id;
    std::optional<std::string> status;
    std::optional<std::string> trading_status;
    std::optional<std::string> trade_volume;
    std::optional<std::string> liquidity;
    /// Price precision of the market, in decimal places. The price tick is 10 to the power of minus
    /// `decimalPrecision`, for example `2` means a tick of 0.01. A limit price that is not on the
    /// tick is truncated down
    std::optional<std::int64_t> decimal_precision;
    std::optional<std::vector<GetMarketDetailResponseMarketsInnerOutcomesInner>> outcomes;

    bool operator==(const GetMarketDetailResponseMarketsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetMarketDetailResponseMarketsInner
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseMarketsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetMarketDetailResponseMarketsInner& v);

} // namespace binance::w3w_prediction::rest_api
