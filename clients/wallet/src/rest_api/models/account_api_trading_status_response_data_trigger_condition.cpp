//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data_trigger_condition.hpp>

namespace binance::wallet::rest_api {

AccountApiTradingStatusResponseDataTriggerCondition
tag_invoke(boost::json::value_to_tag<AccountApiTradingStatusResponseDataTriggerCondition> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountApiTradingStatusResponseDataTriggerCondition");
    AccountApiTradingStatusResponseDataTriggerCondition out;
    common::detail::json::read(obj, "GCR", out.gcr);
    common::detail::json::read(obj, "IFER", out.ifer);
    common::detail::json::read(obj, "UFR", out.ufr);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountApiTradingStatusResponseDataTriggerCondition& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "GCR", v.gcr);
    common::detail::json::write(obj, "IFER", v.ifer);
    common::detail::json::write(obj, "UFR", v.ufr);
}

} // namespace binance::wallet::rest_api
