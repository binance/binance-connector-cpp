//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_small_liability_exchange_history_response_rows_inner.hpp>

namespace binance::margin_trading::rest_api {

GetSmallLiabilityExchangeHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSmallLiabilityExchangeHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSmallLiabilityExchangeHistoryResponseRowsInner");
    GetSmallLiabilityExchangeHistoryResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "targetAsset", out.target_asset);
    common::detail::json::read(obj, "targetAmount", out.target_amount);
    common::detail::json::read(obj, "bizType", out.biz_type);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSmallLiabilityExchangeHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "targetAsset", v.target_asset);
    common::detail::json::write(obj, "targetAmount", v.target_amount);
    common::detail::json::write(obj, "bizType", v.biz_type);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::margin_trading::rest_api
