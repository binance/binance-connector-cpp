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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct MyPreventedMatchesResponseResultInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> prevented_match_id;
    std::optional<std::int64_t> taker_order_id;
    std::optional<std::string> maker_symbol;
    std::optional<std::int64_t> maker_order_id;
    std::optional<std::int64_t> trade_group_id;
    std::optional<std::string> self_trade_prevention_mode;
    std::optional<std::string> price;
    std::optional<std::string> maker_prevented_quantity;
    std::optional<std::int64_t> transact_time;

    bool operator==(const MyPreventedMatchesResponseResultInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyPreventedMatchesResponseResultInner
tag_invoke(boost::json::value_to_tag<MyPreventedMatchesResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyPreventedMatchesResponseResultInner& v);

} // namespace binance::spot::websocket_api
