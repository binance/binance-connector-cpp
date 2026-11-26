//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_summary_of_margin_account_response.hpp>

namespace binance::margin_trading::rest_api {

GetSummaryOfMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetSummaryOfMarginAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetSummaryOfMarginAccountResponse");
    GetSummaryOfMarginAccountResponse out;
    common::detail::json::read(obj, "normalBar", out.normal_bar);
    common::detail::json::read(obj, "marginCallBar", out.margin_call_bar);
    common::detail::json::read(obj, "forceLiquidationBar", out.force_liquidation_bar);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSummaryOfMarginAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "normalBar", v.normal_bar);
    common::detail::json::write(obj, "marginCallBar", v.margin_call_bar);
    common::detail::json::write(obj, "forceLiquidationBar", v.force_liquidation_bar);
}

} // namespace binance::margin_trading::rest_api
