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
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner_address_questionnaire.hpp>

namespace binance::wallet::rest_api {

struct FetchAddressVerificationListResponseInner {
    std::optional<std::string> status;
    std::optional<std::string> token;
    std::optional<std::string> network;
    std::optional<std::string> wallet_address;
    std::optional<FetchAddressVerificationListResponseInnerAddressQuestionnaire>
        address_questionnaire;

    bool operator==(const FetchAddressVerificationListResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT FetchAddressVerificationListResponseInner
tag_invoke(boost::json::value_to_tag<FetchAddressVerificationListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const FetchAddressVerificationListResponseInner& v);

} // namespace binance::wallet::rest_api
