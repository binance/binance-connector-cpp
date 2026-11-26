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

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_index_price_constituents_response_constituents_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct QueryIndexPriceConstituentsResponse {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> time;
    std::optional<std::vector<QueryIndexPriceConstituentsResponseConstituentsInner>> constituents;

    bool operator==(const QueryIndexPriceConstituentsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT QueryIndexPriceConstituentsResponse
tag_invoke(boost::json::value_to_tag<QueryIndexPriceConstituentsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryIndexPriceConstituentsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
