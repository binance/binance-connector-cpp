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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/cross_margin_collateral_ratio_response_inner_collaterals_inner.hpp>

namespace binance::margin_trading::rest_api {

struct CrossMarginCollateralRatioResponseInner {
    /// collaterals list.
    std::optional<std::vector<CrossMarginCollateralRatioResponseInnerCollateralsInner>> collaterals;
    /// asset Names list.
    std::optional<std::vector<std::string>> asset_names;

    bool operator==(const CrossMarginCollateralRatioResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT CrossMarginCollateralRatioResponseInner
tag_invoke(boost::json::value_to_tag<CrossMarginCollateralRatioResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const CrossMarginCollateralRatioResponseInner& v);

} // namespace binance::margin_trading::rest_api
