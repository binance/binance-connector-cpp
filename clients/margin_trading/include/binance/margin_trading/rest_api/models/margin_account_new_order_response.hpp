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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_new_order_response_fills_inner.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountNewOrderResponse {
    /// symbol.
    std::optional<std::string> symbol;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// client Order Id.
    std::optional<std::string> client_order_id;
    /// if isolated margin
    std::optional<bool> is_isolated;
    /// transact Time.
    std::optional<std::int64_t> transact_time;
    /// price.
    std::optional<std::string> price;
    /// orig Qty.
    std::optional<std::string> orig_qty;
    /// executed Qty.
    std::optional<std::string> executed_qty;
    /// cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// status.
    std::optional<std::string> status;
    /// time In Force.
    std::optional<std::string> time_in_force;
    /// type.
    std::optional<std::string> type;
    /// side.
    std::optional<std::string> side;
    /// self Trade Prevention Mode.
    std::optional<std::string> self_trade_prevention_mode;
    /// margin Buy Borrow Amount.
    std::optional<std::int64_t> margin_buy_borrow_amount;
    /// margin Buy Borrow Asset.
    std::optional<std::string> margin_buy_borrow_asset;
    /// fills list.
    std::optional<std::vector<MarginAccountNewOrderResponseFillsInner>> fills;

    bool operator==(const MarginAccountNewOrderResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderResponse tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const MarginAccountNewOrderResponse& v);

} // namespace binance::margin_trading::rest_api
