//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_detail_response_data_profit_transfer_details_inner.hpp>

namespace binance::mining::rest_api {

HashrateResaleDetailResponseDataProfitTransferDetailsInner tag_invoke(
    boost::json::value_to_tag<HashrateResaleDetailResponseDataProfitTransferDetailsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "HashrateResaleDetailResponseDataProfitTransferDetailsInner");
    HashrateResaleDetailResponseDataProfitTransferDetailsInner out;
    common::detail::json::read(obj, "poolUsername", out.pool_username);
    common::detail::json::read(obj, "toPoolUsername", out.to_pool_username);
    common::detail::json::read(obj, "algoName", out.algo_name);
    common::detail::json::read(obj, "hashRate", out.hash_rate);
    common::detail::json::read(obj, "day", out.day);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "coinName", out.coin_name);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const HashrateResaleDetailResponseDataProfitTransferDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "poolUsername", v.pool_username);
    common::detail::json::write(obj, "toPoolUsername", v.to_pool_username);
    common::detail::json::write(obj, "algoName", v.algo_name);
    common::detail::json::write(obj, "hashRate", v.hash_rate);
    common::detail::json::write(obj, "day", v.day);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "coinName", v.coin_name);
}

} // namespace binance::mining::rest_api
