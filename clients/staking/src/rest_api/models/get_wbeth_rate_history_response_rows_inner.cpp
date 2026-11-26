//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rate_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

GetWbethRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetWbethRateHistoryResponseRowsInner");
    GetWbethRateHistoryResponseRowsInner out;
    common::detail::json::read(obj, "annualPercentageRate", out.annual_percentage_rate);
    common::detail::json::read(obj, "exchangeRate", out.exchange_rate);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetWbethRateHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "annualPercentageRate", v.annual_percentage_rate);
    common::detail::json::write(obj, "exchangeRate", v.exchange_rate);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::staking::rest_api
