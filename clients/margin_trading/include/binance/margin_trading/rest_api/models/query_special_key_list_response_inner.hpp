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

struct QuerySpecialKeyListResponseInner {
    /// api Name.
    std::optional<std::string> api_name;
    /// api Key.
    std::optional<std::string> api_key;
    /// ip.
    std::optional<std::string> ip;
    /// type.
    std::optional<std::string> type;
    /// permission Mode.
    std::optional<std::string> permission_mode;

    bool operator==(const QuerySpecialKeyListResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QuerySpecialKeyListResponseInner
tag_invoke(boost::json::value_to_tag<QuerySpecialKeyListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QuerySpecialKeyListResponseInner& v);

} // namespace binance::margin_trading::rest_api
