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
#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct AccountBlockTradeListResponseInnerLegsInner {
    /// create Time
    std::optional<std::int64_t> create_time;
    /// update Time
    std::optional<std::int64_t> update_time;
    /// symbol
    std::optional<std::string> symbol;
    /// order Id
    std::optional<std::string> order_id;
    /// order Price
    std::optional<common::Decimal> order_price;
    /// order Quantity
    std::optional<common::Decimal> order_quantity;
    /// order Status
    std::optional<std::string> order_status;
    /// executed Qty
    std::optional<common::Decimal> executed_qty;
    /// executed Amount
    std::optional<common::Decimal> executed_amount;
    /// fee
    std::optional<common::Decimal> fee;
    /// order Type
    std::optional<std::string> order_type;
    /// order Side
    std::optional<std::string> order_side;
    /// id
    std::optional<std::string> id;
    /// trade Id
    std::optional<std::int64_t> trade_id;
    /// trade Price
    std::optional<common::Decimal> trade_price;
    /// trade Qty
    std::optional<common::Decimal> trade_qty;
    /// trade Time
    std::optional<std::int64_t> trade_time;
    /// liquidity
    std::optional<std::string> liquidity;
    /// commission
    std::optional<common::Decimal> commission;

    bool operator==(const AccountBlockTradeListResponseInnerLegsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountBlockTradeListResponseInnerLegsInner
tag_invoke(boost::json::value_to_tag<AccountBlockTradeListResponseInnerLegsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountBlockTradeListResponseInnerLegsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
