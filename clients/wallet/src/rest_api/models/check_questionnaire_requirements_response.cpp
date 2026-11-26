//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/check_questionnaire_requirements_response.hpp>

namespace binance::wallet::rest_api {

CheckQuestionnaireRequirementsResponse
tag_invoke(boost::json::value_to_tag<CheckQuestionnaireRequirementsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CheckQuestionnaireRequirementsResponse");
    CheckQuestionnaireRequirementsResponse out;
    common::detail::json::read(obj, "questionnaireCountryCode", out.questionnaire_country_code);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CheckQuestionnaireRequirementsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "questionnaireCountryCode", v.questionnaire_country_code);
}

} // namespace binance::wallet::rest_api
