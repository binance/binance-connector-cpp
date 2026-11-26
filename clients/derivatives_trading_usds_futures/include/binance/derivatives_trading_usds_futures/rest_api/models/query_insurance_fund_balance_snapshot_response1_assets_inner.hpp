//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct QueryInsuranceFundBalanceSnapshotResponse1AssetsInner {
    std::optional<std::string> asset;
    std::optional<std::string> margin_balance;
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryInsuranceFundBalanceSnapshotResponse1AssetsInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
QueryInsuranceFundBalanceSnapshotResponse1AssetsInner
tag_invoke(boost::json::value_to_tag<QueryInsuranceFundBalanceSnapshotResponse1AssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryInsuranceFundBalanceSnapshotResponse1AssetsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
