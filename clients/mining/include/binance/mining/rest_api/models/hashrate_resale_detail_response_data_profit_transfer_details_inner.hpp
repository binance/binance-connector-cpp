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

#include <binance/common/decimal.hpp>
#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct HashrateResaleDetailResponseDataProfitTransferDetailsInner {
    /// Transfer-out sub-account
    std::optional<std::string> pool_username;
    /// Transfer-in sub-account
    std::optional<std::string> to_pool_username;
    /// Transfer algorithm name
    std::optional<std::string> algo_name;
    /// Transferred hashrate
    std::optional<std::int64_t> hash_rate;
    /// Transfer date
    std::optional<std::int64_t> day;
    /// Transferred income
    std::optional<common::Decimal> amount;
    /// Income coin
    std::optional<std::string> coin_name;

    bool operator==(const HashrateResaleDetailResponseDataProfitTransferDetailsInner& /*other*/)
        const = default;
};

BINANCE_MINING_EXPORT HashrateResaleDetailResponseDataProfitTransferDetailsInner tag_invoke(
    boost::json::value_to_tag<HashrateResaleDetailResponseDataProfitTransferDetailsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_MINING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const HashrateResaleDetailResponseDataProfitTransferDetailsInner& v);

} // namespace binance::mining::rest_api
