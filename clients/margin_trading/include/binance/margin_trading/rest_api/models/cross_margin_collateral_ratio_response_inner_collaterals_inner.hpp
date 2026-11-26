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

struct CrossMarginCollateralRatioResponseInnerCollateralsInner {
    /// min Usd Value.
    std::optional<std::string> min_usd_value;
    /// max Usd Value.
    std::optional<std::string> max_usd_value;
    /// discount Rate.
    std::optional<std::string> discount_rate;

    bool operator==(
        const CrossMarginCollateralRatioResponseInnerCollateralsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT CrossMarginCollateralRatioResponseInnerCollateralsInner tag_invoke(
    boost::json::value_to_tag<CrossMarginCollateralRatioResponseInnerCollateralsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CrossMarginCollateralRatioResponseInnerCollateralsInner& v);

} // namespace binance::margin_trading::rest_api
