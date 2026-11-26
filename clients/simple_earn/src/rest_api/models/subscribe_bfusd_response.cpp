//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_bfusd_response.hpp>

namespace binance::simple_earn::rest_api {

SubscribeBfusdResponse tag_invoke(boost::json::value_to_tag<SubscribeBfusdResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubscribeBfusdResponse");
    SubscribeBfusdResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "bfusdAmount", out.bfusd_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubscribeBfusdResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "bfusdAmount", v.bfusd_amount);
}

} // namespace binance::simple_earn::rest_api
