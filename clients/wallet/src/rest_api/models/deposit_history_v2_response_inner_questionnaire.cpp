//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner_questionnaire.hpp>

namespace binance::wallet::rest_api {

DepositHistoryV2ResponseInnerQuestionnaire
tag_invoke(boost::json::value_to_tag<DepositHistoryV2ResponseInnerQuestionnaire> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "DepositHistoryV2ResponseInnerQuestionnaire");
    DepositHistoryV2ResponseInnerQuestionnaire out;
    common::detail::json::read(obj, "vaspName", out.vasp_name);
    common::detail::json::read(obj, "depositOriginator", out.deposit_originator);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DepositHistoryV2ResponseInnerQuestionnaire& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "vaspName", v.vasp_name);
    common::detail::json::write(obj, "depositOriginator", v.deposit_originator);
}

} // namespace binance::wallet::rest_api
