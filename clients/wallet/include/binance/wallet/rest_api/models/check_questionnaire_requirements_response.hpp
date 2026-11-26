//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct CheckQuestionnaireRequirementsResponse {
    std::optional<std::string> questionnaire_country_code;

    bool operator==(const CheckQuestionnaireRequirementsResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT CheckQuestionnaireRequirementsResponse
tag_invoke(boost::json::value_to_tag<CheckQuestionnaireRequirementsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CheckQuestionnaireRequirementsResponse& v);

} // namespace binance::wallet::rest_api
