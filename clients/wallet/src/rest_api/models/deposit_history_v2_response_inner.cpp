//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner.hpp>

namespace binance::wallet::rest_api {

DepositHistoryV2ResponseInner
tag_invoke(boost::json::value_to_tag<DepositHistoryV2ResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DepositHistoryV2ResponseInner");
    DepositHistoryV2ResponseInner out;
    common::detail::json::read(obj, "depositId", out.deposit_id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "depositStatus", out.deposit_status);
    common::detail::json::read(obj, "travelRuleReqStatus", out.travel_rule_req_status);
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "addressTag", out.address_tag);
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "transferType", out.transfer_type);
    common::detail::json::read(obj, "confirmTimes", out.confirm_times);
    common::detail::json::read(obj, "requireQuestionnaire", out.require_questionnaire);
    common::detail::json::read(obj, "questionnaire", out.questionnaire);
    common::detail::json::read(obj, "insertTime", out.insert_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DepositHistoryV2ResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "depositId", v.deposit_id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "depositStatus", v.deposit_status);
    common::detail::json::write(obj, "travelRuleReqStatus", v.travel_rule_req_status);
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "addressTag", v.address_tag);
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "transferType", v.transfer_type);
    common::detail::json::write(obj, "confirmTimes", v.confirm_times);
    common::detail::json::write(obj, "requireQuestionnaire", v.require_questionnaire);
    common::detail::json::write(obj, "questionnaire", v.questionnaire);
    common::detail::json::write(obj, "insertTime", v.insert_time);
}

} // namespace binance::wallet::rest_api
