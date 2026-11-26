//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/lot_size_filter.hpp>

namespace binance::spot::websocket_api {

LotSizeFilter tag_invoke(boost::json::value_to_tag<LotSizeFilter> /*tag*/,
                         const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "LotSizeFilter");
    LotSizeFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "qtyExponent", out.qty_exponent);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "stepSize", out.step_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const LotSizeFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "qtyExponent", v.qty_exponent);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "stepSize", v.step_size);
}

} // namespace binance::spot::websocket_api
