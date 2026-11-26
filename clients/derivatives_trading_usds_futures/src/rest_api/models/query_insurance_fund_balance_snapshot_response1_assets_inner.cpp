//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_insurance_fund_balance_snapshot_response1_assets_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

QueryInsuranceFundBalanceSnapshotResponse1AssetsInner
tag_invoke(boost::json::value_to_tag<QueryInsuranceFundBalanceSnapshotResponse1AssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryInsuranceFundBalanceSnapshotResponse1AssetsInner");
    QueryInsuranceFundBalanceSnapshotResponse1AssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "marginBalance", out.margin_balance);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryInsuranceFundBalanceSnapshotResponse1AssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "marginBalance", v.margin_balance);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
