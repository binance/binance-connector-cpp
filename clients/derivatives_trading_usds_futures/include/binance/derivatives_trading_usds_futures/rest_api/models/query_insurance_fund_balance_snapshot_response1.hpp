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

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_insurance_fund_balance_snapshot_response1_assets_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct QueryInsuranceFundBalanceSnapshotResponse1 {
    std::optional<std::vector<std::string>> symbols;
    std::optional<std::vector<QueryInsuranceFundBalanceSnapshotResponse1AssetsInner>> assets;

    bool operator==(const QueryInsuranceFundBalanceSnapshotResponse1& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT QueryInsuranceFundBalanceSnapshotResponse1
tag_invoke(boost::json::value_to_tag<QueryInsuranceFundBalanceSnapshotResponse1> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryInsuranceFundBalanceSnapshotResponse1& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
