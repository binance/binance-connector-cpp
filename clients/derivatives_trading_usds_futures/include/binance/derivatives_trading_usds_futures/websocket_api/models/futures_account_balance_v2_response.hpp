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
#include <binance/derivatives_trading_usds_futures/websocket_api/models/account_information_response_rate_limits_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/futures_account_balance_response_result_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct FuturesAccountBalanceV2Response {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<FuturesAccountBalanceResponseResultInner>> result;
    std::optional<std::vector<AccountInformationResponseRateLimitsInner>> rate_limits;

    bool operator==(const FuturesAccountBalanceV2Response& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT FuturesAccountBalanceV2Response
tag_invoke(boost::json::value_to_tag<FuturesAccountBalanceV2Response> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesAccountBalanceV2Response& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
