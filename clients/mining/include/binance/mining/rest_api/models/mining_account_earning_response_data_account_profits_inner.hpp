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

struct MiningAccountEarningResponseDataAccountProfitsInner {
    /// Time
    std::optional<std::int64_t> time;
    /// Coin
    std::optional<std::string> coin_name;
    /// 0: Referral, 1: Refund, 2: Rebate
    std::optional<std::int64_t> type;
    /// Mining sub-account ID
    std::optional<std::int64_t> puid;
    /// Mining account
    std::optional<std::string> sub_name;
    /// Amount
    std::optional<common::Decimal> amount;

    bool operator==(const MiningAccountEarningResponseDataAccountProfitsInner& /*other*/) const =
        default;
};

BINANCE_MINING_EXPORT MiningAccountEarningResponseDataAccountProfitsInner
tag_invoke(boost::json::value_to_tag<MiningAccountEarningResponseDataAccountProfitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const MiningAccountEarningResponseDataAccountProfitsInner& v);

} // namespace binance::mining::rest_api
