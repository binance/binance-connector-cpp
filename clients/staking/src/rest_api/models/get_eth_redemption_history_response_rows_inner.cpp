//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_eth_redemption_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetEthRedemptionHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetEthRedemptionHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetEthRedemptionHistoryResponseRowsInner");
    GetEthRedemptionHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "arrivalTime", out.arrival_time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "distributeAsset", out.distribute_asset);
    common::detail::json::read(obj, "distributeAmount", out.distribute_amount);
    common::detail::json::read(obj, "conversionRatio", out.conversion_ratio);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetEthRedemptionHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "arrivalTime", v.arrival_time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "distributeAsset", v.distribute_asset);
    common::detail::json::write(obj, "distributeAmount", v.distribute_amount);
    common::detail::json::write(obj, "conversionRatio", v.conversion_ratio);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::staking::rest_api
