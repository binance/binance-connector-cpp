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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct AccountTradeListResponseInner {
    /// unique id
    std::optional<std::int64_t> id;
    /// trade id
    std::optional<std::int64_t> trade_id;
    /// order id
    std::optional<std::int64_t> order_id;
    /// option symbol
    std::optional<std::string> symbol;
    /// trade price
    std::optional<std::string> price;
    /// trade quantity
    std::optional<std::string> quantity;
    /// fee(negative is fee deduction)
    std::optional<std::string> fee;
    /// realized profit/loss
    std::optional<std::string> realized_profit;
    /// order side
    std::optional<std::string> side;
    /// order type
    std::optional<std::string> type;
    /// TAKER or MAKER
    std::optional<std::string> liquidity;
    /// trade time
    std::optional<std::int64_t> time;
    /// price Scale
    std::optional<std::int64_t> price_scale;
    /// quantity Scale
    std::optional<std::int64_t> quantity_scale;
    /// option Side
    std::optional<std::string> option_side;
    /// quote Asset
    std::optional<std::string> quote_asset;

    bool operator==(const AccountTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountTradeListResponseInner tag_invoke(
    boost::json::value_to_tag<AccountTradeListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const AccountTradeListResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
