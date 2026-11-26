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

struct GetMarketDetailResponseMarketsInnerOutcomesInner {
    std::optional<std::string> name;
    std::optional<std::string> price;
    std::optional<std::string> chance;
    std::optional<std::int64_t> index;
    std::optional<std::string> token_id;
    /// Whether this outcome won. Returned only after the market is resolved. More than one outcome
    /// can be `true` when the payout is split
    std::optional<bool> winner;

    bool
    operator==(const GetMarketDetailResponseMarketsInnerOutcomesInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetMarketDetailResponseMarketsInnerOutcomesInner
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseMarketsInnerOutcomesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetMarketDetailResponseMarketsInnerOutcomesInner& v);

} // namespace binance::w3w_prediction::rest_api
