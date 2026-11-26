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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

struct GetExchangeInfoResponseDataSymbolsInnerFiltersInner {
    /// Filter type.
    std::optional<std::string> filter_type;
    /// Minimum price.
    std::optional<std::string> min_price;
    /// Maximum price.
    std::optional<std::string> max_price;
    /// Tick size.
    std::optional<std::string> tick_size;
    /// Step size.
    std::optional<std::string> step_size;
    /// Maximum quantity.
    std::optional<std::string> max_qty;
    /// Minimum quantity.
    std::optional<std::string> min_qty;
    /// Maximum allowed orders for this rule.
    std::optional<std::int64_t> limit;
    /// Minimum notional value.
    std::optional<std::string> min_notional;
    /// Maximum notional value.
    std::optional<std::string> max_notional;
    /// Lower multiplier bound.
    std::optional<std::string> multiplier_down;
    /// Upper multiplier bound.
    std::optional<std::string> multiplier_up;
    /// Upper multiplier bound for bids.
    std::optional<std::string> bid_multiplier_up;
    /// Upper multiplier bound for asks.
    std::optional<std::string> ask_multiplier_up;
    /// Lower multiplier bound for bids.
    std::optional<std::string> bid_multiplier_down;
    /// Lower multiplier bound for asks.
    std::optional<std::string> ask_multiplier_down;

    bool operator==(const GetExchangeInfoResponseDataSymbolsInnerFiltersInner& /*other*/) const =
        default;
};

BINANCE_ALPHA_EXPORT GetExchangeInfoResponseDataSymbolsInnerFiltersInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataSymbolsInnerFiltersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const GetExchangeInfoResponseDataSymbolsInnerFiltersInner& v);

} // namespace binance::alpha::rest_api
