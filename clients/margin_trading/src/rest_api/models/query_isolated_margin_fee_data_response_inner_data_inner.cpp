//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_fee_data_response_inner_data_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginFeeDataResponseInnerDataInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginFeeDataResponseInnerDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryIsolatedMarginFeeDataResponseInnerDataInner");
    QueryIsolatedMarginFeeDataResponseInnerDataInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "dailyInterest", out.daily_interest);
    common::detail::json::read(obj, "borrowLimit", out.borrow_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginFeeDataResponseInnerDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "dailyInterest", v.daily_interest);
    common::detail::json::write(obj, "borrowLimit", v.borrow_limit);
}

} // namespace binance::margin_trading::rest_api
