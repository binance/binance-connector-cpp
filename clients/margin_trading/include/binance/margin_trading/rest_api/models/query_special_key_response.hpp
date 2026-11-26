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

struct QuerySpecialKeyResponse {
    /// api Key.
    std::optional<std::string> api_key;
    /// 0.0.0.0 is just an initial statereference (no extra meaning).
    std::optional<std::string> ip;
    /// api Name.
    std::optional<std::string> api_name;
    /// type.
    std::optional<std::string> type;
    /// permission Mode.
    std::optional<std::string> permission_mode;

    bool operator==(const QuerySpecialKeyResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QuerySpecialKeyResponse tag_invoke(
    boost::json::value_to_tag<QuerySpecialKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QuerySpecialKeyResponse& v);

} // namespace binance::margin_trading::rest_api
