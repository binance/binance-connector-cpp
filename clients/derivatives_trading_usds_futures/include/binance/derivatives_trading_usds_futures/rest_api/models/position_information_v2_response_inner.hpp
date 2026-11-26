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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct PositionInformationV2ResponseInner {
    /// Entry Price.
    std::optional<std::string> entry_price;
    /// Break Even Price.
    std::optional<std::string> break_even_price;
    /// Margin Type.
    std::optional<std::string> margin_type;
    std::optional<std::string> is_auto_add_margin;
    /// Isolated Margin.
    std::optional<std::string> isolated_margin;
    /// Leverage.
    std::optional<std::string> leverage;
    /// Liquidation Price.
    std::optional<std::string> liquidation_price;
    /// Mark Price.
    std::optional<std::string> mark_price;
    /// Max Notional Value.
    std::optional<std::string> max_notional_value;
    /// Position Amt.
    std::optional<std::string> position_amt;
    std::optional<std::string> notional;
    std::optional<std::string> isolated_wallet;
    /// Symbol.
    std::optional<std::string> symbol;
    /// Un Realized Profit.
    std::optional<std::string> un_realized_profit;
    /// Position Side.
    std::optional<std::string> position_side;
    /// Update Time.
    std::optional<std::int64_t> update_time;

    bool operator==(const PositionInformationV2ResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PositionInformationV2ResponseInner
tag_invoke(boost::json::value_to_tag<PositionInformationV2ResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionInformationV2ResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
