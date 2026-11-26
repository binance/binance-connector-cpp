//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/mining_account_earning_response_data_account_profits_inner.hpp>

namespace binance::mining::rest_api {

MiningAccountEarningResponseDataAccountProfitsInner
tag_invoke(boost::json::value_to_tag<MiningAccountEarningResponseDataAccountProfitsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "MiningAccountEarningResponseDataAccountProfitsInner");
    MiningAccountEarningResponseDataAccountProfitsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "coinName", out.coin_name);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "puid", out.puid);
    common::detail::json::read(obj, "subName", out.sub_name);
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MiningAccountEarningResponseDataAccountProfitsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "coinName", v.coin_name);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "puid", v.puid);
    common::detail::json::write(obj, "subName", v.sub_name);
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::mining::rest_api
