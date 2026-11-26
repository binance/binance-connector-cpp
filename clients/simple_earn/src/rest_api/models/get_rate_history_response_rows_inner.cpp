//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_rate_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetRateHistoryResponseRowsInner");
    GetRateHistoryResponseRowsInner out;
    common::detail::json::read(obj, "productId", out.product_id);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRateHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "productId", v.product_id);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::simple_earn::rest_api
