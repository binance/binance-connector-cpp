//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/earnings_list_response_data_account_profits_inner.hpp>

namespace binance::mining::rest_api {

EarningsListResponseDataAccountProfitsInner
tag_invoke(boost::json::value_to_tag<EarningsListResponseDataAccountProfitsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "EarningsListResponseDataAccountProfitsInner");
    EarningsListResponseDataAccountProfitsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "hashTransfer", out.hash_transfer);
    common::detail::json::read(obj, "transferAmount", out.transfer_amount);
    common::detail::json::read(obj, "dayHashRate", out.day_hash_rate);
    common::detail::json::read(obj, "profitAmount", out.profit_amount);
    common::detail::json::read(obj, "coinName", out.coin_name);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EarningsListResponseDataAccountProfitsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "hashTransfer", v.hash_transfer);
    common::detail::json::write(obj, "transferAmount", v.transfer_amount);
    common::detail::json::write(obj, "dayHashRate", v.day_hash_rate);
    common::detail::json::write(obj, "profitAmount", v.profit_amount);
    common::detail::json::write(obj, "coinName", v.coin_name);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::mining::rest_api
