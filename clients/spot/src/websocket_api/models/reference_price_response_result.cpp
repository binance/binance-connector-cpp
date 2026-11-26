//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/reference_price_response_result.hpp>

namespace binance::spot::websocket_api {

ReferencePriceResponseResult
tag_invoke(boost::json::value_to_tag<ReferencePriceResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ReferencePriceResponseResult");
    ReferencePriceResponseResult out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "referencePrice", out.reference_price);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ReferencePriceResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "referencePrice", v.reference_price);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::spot::websocket_api
