//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/get_convert_trade_history_response.hpp>

namespace binance::convert::rest_api {

GetConvertTradeHistoryResponse
tag_invoke(boost::json::value_to_tag<GetConvertTradeHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetConvertTradeHistoryResponse");
    GetConvertTradeHistoryResponse out;
    common::detail::json::read(obj, "list", out.list);
    common::detail::json::read(obj, "startTime", out.start_time);
    common::detail::json::read(obj, "endTime", out.end_time);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "moreData", out.more_data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetConvertTradeHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "list", v.list);
    common::detail::json::write(obj, "startTime", v.start_time);
    common::detail::json::write(obj, "endTime", v.end_time);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "moreData", v.more_data);
}

} // namespace binance::convert::rest_api
