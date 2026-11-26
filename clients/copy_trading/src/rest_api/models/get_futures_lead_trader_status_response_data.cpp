//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trader_status_response_data.hpp>

namespace binance::copy_trading::rest_api {

GetFuturesLeadTraderStatusResponseData
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTraderStatusResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetFuturesLeadTraderStatusResponseData");
    GetFuturesLeadTraderStatusResponseData out;
    common::detail::json::read(obj, "isLeadTrader", out.is_lead_trader);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFuturesLeadTraderStatusResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "isLeadTrader", v.is_lead_trader);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::copy_trading::rest_api
