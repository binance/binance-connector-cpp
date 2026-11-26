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

struct QueryIsolatedMarginTierDataResponseInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// tier.
    std::optional<std::int64_t> tier;
    /// effective Multiple.
    std::optional<std::string> effective_multiple;
    /// initial Risk Ratio.
    std::optional<std::string> initial_risk_ratio;
    /// liquidation Risk Ratio.
    std::optional<std::string> liquidation_risk_ratio;
    /// base Asset Max Borrowable.
    std::optional<std::string> base_asset_max_borrowable;
    /// quote Asset Max Borrowable.
    std::optional<std::string> quote_asset_max_borrowable;

    bool operator==(const QueryIsolatedMarginTierDataResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryIsolatedMarginTierDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginTierDataResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryIsolatedMarginTierDataResponseInner& v);

} // namespace binance::margin_trading::rest_api
