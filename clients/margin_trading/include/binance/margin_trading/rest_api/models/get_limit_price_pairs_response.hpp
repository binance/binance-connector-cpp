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

namespace binance::margin_trading::rest_api {

struct GetLimitPricePairsResponse {
    /// cross Margin Symbols list.
    std::optional<std::vector<std::string>> cross_margin_symbols;

    bool operator==(const GetLimitPricePairsResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetLimitPricePairsResponse tag_invoke(
    boost::json::value_to_tag<GetLimitPricePairsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetLimitPricePairsResponse& v);

} // namespace binance::margin_trading::rest_api
