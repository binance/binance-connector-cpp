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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data_trigger_condition.hpp>

namespace binance::wallet::rest_api {

struct AccountApiTradingStatusResponseData {
    /// API trading function is locked or not
    std::optional<bool> is_locked;
    /// If API trading function is locked, this is the planned recover time
    std::optional<std::int64_t> planned_recover_time;
    std::optional<AccountApiTradingStatusResponseDataTriggerCondition> trigger_condition;
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountApiTradingStatusResponseData& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AccountApiTradingStatusResponseData
tag_invoke(boost::json::value_to_tag<AccountApiTradingStatusResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountApiTradingStatusResponseData& v);

} // namespace binance::wallet::rest_api
