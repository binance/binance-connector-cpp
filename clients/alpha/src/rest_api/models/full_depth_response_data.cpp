//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/full_depth_response_data.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

FullDepthResponseData tag_invoke(boost::json::value_to_tag<FullDepthResponseData> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FullDepthResponseData");
    FullDepthResponseData out;
    common::detail::json::read(obj, "lastUpdateId", out.last_update_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "bids", out.bids);
    common::detail::json::read(obj, "asks", out.asks);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FullDepthResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "lastUpdateId", v.last_update_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "bids", v.bids);
    common::detail::json::write(obj, "asks", v.asks);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
}

} // namespace binance::alpha::rest_api
