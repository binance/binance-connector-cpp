//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quota_status_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetQuotaStatusResponse tag_invoke(boost::json::value_to_tag<GetQuotaStatusResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetQuotaStatusResponse");
    GetQuotaStatusResponse out;
    common::detail::json::read(obj, "dailyLimit", out.daily_limit);
    common::detail::json::read(obj, "remainingDailyLimit", out.remaining_daily_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetQuotaStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "dailyLimit", v.daily_limit);
    common::detail::json::write(obj, "remainingDailyLimit", v.remaining_daily_limit);
}

} // namespace binance::w3w_prediction::rest_api
