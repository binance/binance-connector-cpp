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

#include <binance/c2c/export.hpp>

namespace binance::c2c::rest_api {

struct GetC2CTradeHistoryResponseDataInner {
    /// Order Number
    std::optional<std::string> order_number;
    /// Adv Number
    std::optional<std::string> adv_no;
    /// "BUY" or "SELL"
    std::optional<std::string> trade_type;
    /// Crypto asset
    std::optional<std::string> asset;
    /// Fiat currency
    std::optional<std::string> fiat;
    /// Fiat currency symbol
    std::optional<std::string> fiat_symbol;
    /// Quantity (in Crypto)
    std::optional<std::string> amount;
    /// Total order amount in fiat
    std::optional<std::string> total_price;
    /// Unit Price (in Fiat)
    std::optional<std::string> unit_price;
    /// PENDING, TRADING, BUYER_PAYED, DISTRIBUTING, COMPLETED, IN_APPEAL, CANCELLED,
    /// CANCELLED_BY_SYSTEM
    std::optional<std::string> order_status;
    /// Order creation timestamp in milliseconds
    std::optional<std::int64_t> create_time;
    /// Transaction Fee (in Crypto)
    std::optional<std::string> commission;
    /// Counterparty nickname
    std::optional<std::string> counter_part_nick_name;
    /// Identifier of the payment method
    std::optional<std::string> pay_method_name;
    /// KYC verification status. 0: not required, 1: not verified, 2: verified
    std::optional<std::int64_t> additional_kyc_verify;
    /// Taker commission rate
    std::optional<std::string> taker_commission_rate;
    /// Taker commission amount
    std::optional<std::string> taker_commission;
    /// Taker trade amount
    std::optional<std::string> taker_amount;
    std::optional<std::string> advertisement_role;

    bool operator==(const GetC2CTradeHistoryResponseDataInner& /*other*/) const = default;
};

BINANCE_C2C_EXPORT GetC2CTradeHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetC2CTradeHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_C2C_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetC2CTradeHistoryResponseDataInner& v);

} // namespace binance::c2c::rest_api
