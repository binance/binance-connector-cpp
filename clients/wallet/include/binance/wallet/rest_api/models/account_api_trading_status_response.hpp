//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data.hpp>

namespace binance::wallet::rest_api {

struct AccountApiTradingStatusResponse {
    std::optional<AccountApiTradingStatusResponseData> data;

    bool operator==(const AccountApiTradingStatusResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AccountApiTradingStatusResponse
tag_invoke(boost::json::value_to_tag<AccountApiTradingStatusResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountApiTradingStatusResponse& v);

} // namespace binance::wallet::rest_api
