//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/aggregated_trades_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

AggregatedTradesResponse tag_invoke(boost::json::value_to_tag<AggregatedTradesResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AggregatedTradesResponse");
    AggregatedTradesResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "messageDetail", out.message_detail);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AggregatedTradesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "messageDetail", v.message_detail);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::alpha::rest_api
