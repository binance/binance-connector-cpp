//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_insurance_fund_balance_snapshot_response1.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

QueryInsuranceFundBalanceSnapshotResponse1
tag_invoke(boost::json::value_to_tag<QueryInsuranceFundBalanceSnapshotResponse1> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryInsuranceFundBalanceSnapshotResponse1");
    QueryInsuranceFundBalanceSnapshotResponse1 out;
    common::detail::json::read(obj, "symbols", out.symbols);
    common::detail::json::read(obj, "assets", out.assets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryInsuranceFundBalanceSnapshotResponse1& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbols", v.symbols);
    common::detail::json::write(obj, "assets", v.assets);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
