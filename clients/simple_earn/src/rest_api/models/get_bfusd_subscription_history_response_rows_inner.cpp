//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_subscription_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdSubscriptionHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBfusdSubscriptionHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBfusdSubscriptionHistoryResponseRowsInner");
    GetBfusdSubscriptionHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "receiveAsset", out.receive_asset);
    common::detail::json::read(obj, "receiveAmount", out.receive_amount);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdSubscriptionHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "receiveAsset", v.receive_asset);
    common::detail::json::write(obj, "receiveAmount", v.receive_amount);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::simple_earn::rest_api
