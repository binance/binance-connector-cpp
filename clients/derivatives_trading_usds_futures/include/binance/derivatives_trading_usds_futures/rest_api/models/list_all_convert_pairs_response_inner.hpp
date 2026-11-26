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

struct ListAllConvertPairsResponseInner {
    std::optional<std::string> from_asset;
    std::optional<std::string> to_asset;
    std::optional<std::string> from_asset_min_amount;
    std::optional<std::string> from_asset_max_amount;
    std::optional<std::string> to_asset_min_amount;
    std::optional<std::string> to_asset_max_amount;

    bool operator==(const ListAllConvertPairsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ListAllConvertPairsResponseInner
tag_invoke(boost::json::value_to_tag<ListAllConvertPairsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ListAllConvertPairsResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
