//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/remove_otc_blocktrades_response.hpp>

namespace binance::w3w_prediction::rest_api {

RemoveOtcBlocktradesResponse
tag_invoke(boost::json::value_to_tag<RemoveOtcBlocktradesResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RemoveOtcBlocktradesResponse");
    RemoveOtcBlocktradesResponse out;
    common::detail::json::read(obj, "removed", out.removed);
    common::detail::json::read(obj, "noop", out.noop);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RemoveOtcBlocktradesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "removed", v.removed);
    common::detail::json::write(obj, "noop", v.noop);
}

} // namespace binance::w3w_prediction::rest_api
