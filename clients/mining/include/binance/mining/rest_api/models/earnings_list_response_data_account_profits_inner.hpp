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

struct EarningsListResponseDataAccountProfitsInner {
    /// Mining date
    std::optional<std::int64_t> time;
    /// 0: Mining Wallet, 5: Mining Address, 7: Pool Savings, 8: Transferred, 31: Income Transfer,
    /// 32: Hashrate Resale-Mining Wallet, 33: Hashrate Resale-Pool Savings
    std::optional<std::int64_t> type;
    /// Transferred hashrate
    std::optional<std::int64_t> hash_transfer;
    /// Transferred income
    std::optional<common::Decimal> transfer_amount;
    /// Daily hashrate
    std::optional<std::int64_t> day_hash_rate;
    /// Earnings amount
    std::optional<common::Decimal> profit_amount;
    /// Coin type
    std::optional<std::string> coin_name;
    /// Status: 0 Unpaid, 1 Paying, 2 Paid
    std::optional<std::int64_t> status;

    bool operator==(const EarningsListResponseDataAccountProfitsInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT EarningsListResponseDataAccountProfitsInner
tag_invoke(boost::json::value_to_tag<EarningsListResponseDataAccountProfitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EarningsListResponseDataAccountProfitsInner& v);

} // namespace binance::mining::rest_api
