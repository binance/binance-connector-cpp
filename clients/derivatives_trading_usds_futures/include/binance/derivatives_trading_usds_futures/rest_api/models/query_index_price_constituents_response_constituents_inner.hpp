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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct QueryIndexPriceConstituentsResponseConstituentsInner {
    std::optional<std::string> exchange;
    std::optional<std::string> symbol;
    std::optional<std::string> price;
    std::optional<std::string> weight;

    bool operator==(const QueryIndexPriceConstituentsResponseConstituentsInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT QueryIndexPriceConstituentsResponseConstituentsInner
tag_invoke(boost::json::value_to_tag<QueryIndexPriceConstituentsResponseConstituentsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryIndexPriceConstituentsResponseConstituentsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
