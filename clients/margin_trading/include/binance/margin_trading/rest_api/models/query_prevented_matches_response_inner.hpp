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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryPreventedMatchesResponseInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// prevented Match Id.
    std::optional<std::int64_t> prevented_match_id;
    /// taker Order Id.
    std::optional<std::int64_t> taker_order_id;
    /// maker Symbol.
    std::optional<std::string> maker_symbol;
    /// maker Order Id.
    std::optional<std::int64_t> maker_order_id;
    /// trade Group Id.
    std::optional<std::int64_t> trade_group_id;
    /// self Trade Prevention Mode.
    std::optional<std::string> self_trade_prevention_mode;
    /// price.
    std::optional<std::string> price;
    /// maker Prevented Quantity.
    std::optional<std::string> maker_prevented_quantity;
    /// transact Time.
    std::optional<std::int64_t> transact_time;

    bool operator==(const QueryPreventedMatchesResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryPreventedMatchesResponseInner
tag_invoke(boost::json::value_to_tag<QueryPreventedMatchesResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPreventedMatchesResponseInner& v);

} // namespace binance::margin_trading::rest_api
