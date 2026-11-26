//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/mark_price_response1.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/mark_price_response2_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct MarkPriceResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<MarkPriceResponse1, std::vector<MarkPriceResponse2Inner>, boost::json::value>
        value;

    bool operator==(const MarkPriceResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceResponse
tag_invoke(boost::json::value_to_tag<MarkPriceResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const MarkPriceResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
