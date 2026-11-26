//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_order_modify_history_response_inner_amendment_orig_qty.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

GetOrderModifyHistoryResponseInnerAmendmentOrigQty
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInnerAmendmentOrigQty> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOrderModifyHistoryResponseInnerAmendmentOrigQty");
    GetOrderModifyHistoryResponseInnerAmendmentOrigQty out;
    common::detail::json::read(obj, "before", out.before);
    common::detail::json::read(obj, "after", out.after);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOrderModifyHistoryResponseInnerAmendmentOrigQty& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "before", v.before);
    common::detail::json::write(obj, "after", v.after);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
