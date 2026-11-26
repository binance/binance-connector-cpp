//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data.hpp>

namespace binance::wallet::rest_api {

AccountApiTradingStatusResponseData
tag_invoke(boost::json::value_to_tag<AccountApiTradingStatusResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountApiTradingStatusResponseData");
    AccountApiTradingStatusResponseData out;
    common::detail::json::read(obj, "isLocked", out.is_locked);
    common::detail::json::read(obj, "plannedRecoverTime", out.planned_recover_time);
    common::detail::json::read(obj, "triggerCondition", out.trigger_condition);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountApiTradingStatusResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "isLocked", v.is_locked);
    common::detail::json::write(obj, "plannedRecoverTime", v.planned_recover_time);
    common::detail::json::write(obj, "triggerCondition", v.trigger_condition);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::wallet::rest_api
