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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionSettlementEventDetailResponseCollateralReleaseInner {
    /// Asset released.
    std::optional<std::string> symbol;
    /// Amount released.
    std::optional<std::string> amount;

    bool operator==(
        const OptionSettlementEventDetailResponseCollateralReleaseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionSettlementEventDetailResponseCollateralReleaseInner tag_invoke(
    boost::json::value_to_tag<OptionSettlementEventDetailResponseCollateralReleaseInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionSettlementEventDetailResponseCollateralReleaseInner& v);

} // namespace binance::stock_options::rest_api
