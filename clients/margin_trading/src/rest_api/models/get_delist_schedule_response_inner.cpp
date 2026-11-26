//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_delist_schedule_response_inner.hpp>

namespace binance::margin_trading::rest_api {

GetDelistScheduleResponseInner
tag_invoke(boost::json::value_to_tag<GetDelistScheduleResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetDelistScheduleResponseInner");
    GetDelistScheduleResponseInner out;
    common::detail::json::read(obj, "delistTime", out.delist_time);
    common::detail::json::read(obj, "crossMarginAssets", out.cross_margin_assets);
    common::detail::json::read(obj, "isolatedMarginSymbols", out.isolated_margin_symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDelistScheduleResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "delistTime", v.delist_time);
    common::detail::json::write(obj, "crossMarginAssets", v.cross_margin_assets);
    common::detail::json::write(obj, "isolatedMarginSymbols", v.isolated_margin_symbols);
}

} // namespace binance::margin_trading::rest_api
