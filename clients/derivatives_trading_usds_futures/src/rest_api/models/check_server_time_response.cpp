//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/check_server_time_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

CheckServerTimeResponse tag_invoke(boost::json::value_to_tag<CheckServerTimeResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CheckServerTimeResponse");
    CheckServerTimeResponse out;
    common::detail::json::read(obj, "serverTime", out.server_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CheckServerTimeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "serverTime", v.server_time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
