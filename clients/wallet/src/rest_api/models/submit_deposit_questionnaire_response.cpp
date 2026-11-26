//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_response.hpp>

namespace binance::wallet::rest_api {

SubmitDepositQuestionnaireResponse
tag_invoke(boost::json::value_to_tag<SubmitDepositQuestionnaireResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubmitDepositQuestionnaireResponse");
    SubmitDepositQuestionnaireResponse out;
    common::detail::json::read(obj, "trId", out.tr_id);
    common::detail::json::read(obj, "accepted", out.accepted);
    common::detail::json::read(obj, "info", out.info);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubmitDepositQuestionnaireResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "trId", v.tr_id);
    common::detail::json::write(obj, "accepted", v.accepted);
    common::detail::json::write(obj, "info", v.info);
}

} // namespace binance::wallet::rest_api
