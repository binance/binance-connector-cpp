//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/c2c/rest_api/models/get_c2c_trade_history_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::c2c::rest_api {

GetC2CTradeHistoryResponse tag_invoke(boost::json::value_to_tag<GetC2CTradeHistoryResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetC2CTradeHistoryResponse");
    GetC2CTradeHistoryResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "data", out.data);
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetC2CTradeHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "data", v.data);
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::c2c::rest_api
