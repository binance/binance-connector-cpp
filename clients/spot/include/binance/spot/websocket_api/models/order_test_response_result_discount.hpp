//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

/// Discount on standard commissions when paying in BNB.
struct OrderTestResponseResultDiscount {
    std::optional<bool> enabled_for_account;
    std::optional<bool> enabled_for_symbol;
    std::optional<std::string> discount_asset;
    /// Standard commission is reduced by this rate when paying commission in BNB.
    std::optional<std::string> discount;

    bool operator==(const OrderTestResponseResultDiscount& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderTestResponseResultDiscount
tag_invoke(boost::json::value_to_tag<OrderTestResponseResultDiscount> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderTestResponseResultDiscount& v);

} // namespace binance::spot::websocket_api
