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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct CancelAllOptionOrdersOnSpecificSymbolResponse {
    /// code
    std::optional<std::string> code;
    /// msg
    std::optional<std::string> msg;

    bool operator==(const CancelAllOptionOrdersOnSpecificSymbolResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT CancelAllOptionOrdersOnSpecificSymbolResponse
tag_invoke(boost::json::value_to_tag<CancelAllOptionOrdersOnSpecificSymbolResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CancelAllOptionOrdersOnSpecificSymbolResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
