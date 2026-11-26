//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/redeem_rwusd_response.hpp>

namespace binance::simple_earn::rest_api {

RedeemRwusdResponse tag_invoke(boost::json::value_to_tag<RedeemRwusdResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RedeemRwusdResponse");
    RedeemRwusdResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "receiveAmount", out.receive_amount);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "arrivalTime", out.arrival_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RedeemRwusdResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "receiveAmount", v.receive_amount);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "arrivalTime", v.arrival_time);
}

} // namespace binance::simple_earn::rest_api
