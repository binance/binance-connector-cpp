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

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct PositionInformationResponseResultInner {
    std::optional<std::string> entry_price;
    std::optional<std::string> break_even_price;
    std::optional<std::string> margin_type;
    std::optional<std::string> is_auto_add_margin;
    std::optional<std::string> isolated_margin;
    std::optional<std::string> leverage;
    std::optional<std::string> liquidation_price;
    std::optional<std::string> mark_price;
    std::optional<std::string> max_notional_value;
    std::optional<std::string> position_amt;
    std::optional<std::string> notional;
    std::optional<std::string> isolated_wallet;
    std::optional<std::string> symbol;
    std::optional<std::string> un_realized_profit;
    std::optional<std::string> position_side;
    std::optional<std::int64_t> update_time;

    bool operator==(const PositionInformationResponseResultInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PositionInformationResponseResultInner
tag_invoke(boost::json::value_to_tag<PositionInformationResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionInformationResponseResultInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
