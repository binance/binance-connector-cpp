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

namespace binance::wallet::rest_api {

struct AccountApiTradingStatusResponseDataTriggerCondition {
    /// Number of GTC orders
    std::optional<std::int64_t> gcr;
    /// Number of FOK/IOC orders
    std::optional<std::int64_t> ifer;
    /// Number of orders
    std::optional<std::int64_t> ufr;

    bool operator==(const AccountApiTradingStatusResponseDataTriggerCondition& /*other*/) const =
        default;
};

BINANCE_WALLET_EXPORT AccountApiTradingStatusResponseDataTriggerCondition
tag_invoke(boost::json::value_to_tag<AccountApiTradingStatusResponseDataTriggerCondition> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountApiTradingStatusResponseDataTriggerCondition& v);

} // namespace binance::wallet::rest_api
