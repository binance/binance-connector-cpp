//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_order_modify_history_response_inner_amendment.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

GetOrderModifyHistoryResponseInnerAmendment
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInnerAmendment> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOrderModifyHistoryResponseInnerAmendment");
    GetOrderModifyHistoryResponseInnerAmendment out;
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "origQty", out.orig_qty);
    common::detail::json::read(obj, "count", out.count);
    common::detail::json::read(obj, "modifyId", out.modify_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOrderModifyHistoryResponseInnerAmendment& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "origQty", v.orig_qty);
    common::detail::json::write(obj, "count", v.count);
    common::detail::json::write(obj, "modifyId", v.modify_id);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
