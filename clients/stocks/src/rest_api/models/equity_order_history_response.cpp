//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/equity_order_history_response.hpp>

namespace binance::stocks::rest_api {

EquityOrderHistoryResponse tag_invoke(boost::json::value_to_tag<EquityOrderHistoryResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EquityOrderHistoryResponse");
    EquityOrderHistoryResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "page", out.page);
    common::detail::json::read(obj, "size", out.size);
    common::detail::json::read(obj, "rows", out.rows);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EquityOrderHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "page", v.page);
    common::detail::json::write(obj, "size", v.size);
    common::detail::json::write(obj, "rows", v.rows);
}

} // namespace binance::stocks::rest_api
