//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_wbeth_wrap_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetWbethWrapHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethWrapHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetWbethWrapHistoryResponseRowsInner");
    GetWbethWrapHistoryResponseRowsInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "fromAsset", out.from_asset);
    common::detail::json::read(obj, "fromAmount", out.from_amount);
    common::detail::json::read(obj, "toAsset", out.to_asset);
    common::detail::json::read(obj, "toAmount", out.to_amount);
    common::detail::json::read(obj, "exchangeRate", out.exchange_rate);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetWbethWrapHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "fromAsset", v.from_asset);
    common::detail::json::write(obj, "fromAmount", v.from_amount);
    common::detail::json::write(obj, "toAsset", v.to_asset);
    common::detail::json::write(obj, "toAmount", v.to_amount);
    common::detail::json::write(obj, "exchangeRate", v.exchange_rate);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::staking::rest_api
