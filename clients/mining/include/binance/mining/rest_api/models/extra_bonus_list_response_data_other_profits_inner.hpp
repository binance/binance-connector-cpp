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

struct ExtraBonusListResponseDataOtherProfitsInner {
    /// Mining date
    std::optional<std::int64_t> time;
    /// Coin name
    std::optional<std::string> coin_name;
    /// 1: Merged Mining, 2: Activity Bonus, 3: Rebate, 4: Smart Pool, 6: Income Transfer, 7: Pool
    /// Savings
    std::optional<std::int64_t> type;
    /// Amount
    std::optional<common::Decimal> profit_amount;
    /// Status: 0 Unpaid, 1 Paying, 2 Paid
    std::optional<std::int64_t> status;

    bool operator==(const ExtraBonusListResponseDataOtherProfitsInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT ExtraBonusListResponseDataOtherProfitsInner
tag_invoke(boost::json::value_to_tag<ExtraBonusListResponseDataOtherProfitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const ExtraBonusListResponseDataOtherProfitsInner& v);

} // namespace binance::mining::rest_api
