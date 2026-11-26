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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct GetSummaryOfMarginAccountResponse {
    /// normal Bar.
    std::optional<std::string> normal_bar;
    /// margin Call Bar.
    std::optional<std::string> margin_call_bar;
    /// force Liquidation Bar.
    std::optional<std::string> force_liquidation_bar;

    bool operator==(const GetSummaryOfMarginAccountResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetSummaryOfMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetSummaryOfMarginAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetSummaryOfMarginAccountResponse& v);

} // namespace binance::margin_trading::rest_api
