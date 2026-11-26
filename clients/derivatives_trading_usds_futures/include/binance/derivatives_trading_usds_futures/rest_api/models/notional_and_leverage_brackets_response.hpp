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
#include <binance/derivatives_trading_usds_futures/rest_api/models/notional_and_leverage_brackets_response1_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/notional_and_leverage_brackets_response2.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct NotionalAndLeverageBracketsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::vector<NotionalAndLeverageBracketsResponse1Inner>,
                 NotionalAndLeverageBracketsResponse2, boost::json::value>
        value;

    bool operator==(const NotionalAndLeverageBracketsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NotionalAndLeverageBracketsResponse
tag_invoke(boost::json::value_to_tag<NotionalAndLeverageBracketsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NotionalAndLeverageBracketsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
