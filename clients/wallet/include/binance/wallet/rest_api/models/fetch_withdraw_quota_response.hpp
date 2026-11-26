//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct FetchWithdrawQuotaResponse {
    /// User's total withdrawal quota in the past 24 hours (including on-chain withdrawal and
    /// internal transfer), unit in USD
    std::optional<std::string> wd_quota;
    /// User withdrawal quota usage in the past 24 hours, unit in USD
    std::optional<std::string> used_wd_quota;

    bool operator==(const FetchWithdrawQuotaResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT FetchWithdrawQuotaResponse tag_invoke(
    boost::json::value_to_tag<FetchWithdrawQuotaResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const FetchWithdrawQuotaResponse& v);

} // namespace binance::wallet::rest_api
