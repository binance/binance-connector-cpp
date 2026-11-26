//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_order_modify_history_response_inner_amendment_price.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

GetOrderModifyHistoryResponseInnerAmendmentPrice
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInnerAmendmentPrice> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOrderModifyHistoryResponseInnerAmendmentPrice");
    GetOrderModifyHistoryResponseInnerAmendmentPrice out;
    common::detail::json::read(obj, "before", out.before);
    common::detail::json::read(obj, "after", out.after);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOrderModifyHistoryResponseInnerAmendmentPrice& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "before", v.before);
    common::detail::json::write(obj, "after", v.after);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
