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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryLastTradePriceResponse {
    std::optional<std::int64_t> market_id;
    std::optional<std::string> last_trade_price;

    bool operator==(const QueryLastTradePriceResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryLastTradePriceResponse tag_invoke(
    boost::json::value_to_tag<QueryLastTradePriceResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryLastTradePriceResponse& v);

} // namespace binance::w3w_prediction::rest_api
