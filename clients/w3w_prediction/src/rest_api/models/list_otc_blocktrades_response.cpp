//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/list_otc_blocktrades_response.hpp>

namespace binance::w3w_prediction::rest_api {

ListOtcBlocktradesResponse tag_invoke(boost::json::value_to_tag<ListOtcBlocktradesResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListOtcBlocktradesResponse");
    ListOtcBlocktradesResponse out;
    common::detail::json::read(obj, "cursor", out.cursor);
    common::detail::json::read(obj, "blocktrades", out.blocktrades);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListOtcBlocktradesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "cursor", v.cursor);
    common::detail::json::write(obj, "blocktrades", v.blocktrades);
}

} // namespace binance::w3w_prediction::rest_api
