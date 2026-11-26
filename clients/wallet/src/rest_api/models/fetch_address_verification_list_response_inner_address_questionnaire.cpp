//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner_address_questionnaire.hpp>

namespace binance::wallet::rest_api {

FetchAddressVerificationListResponseInnerAddressQuestionnaire
tag_invoke(boost::json::value_to_tag<
               FetchAddressVerificationListResponseInnerAddressQuestionnaire> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "FetchAddressVerificationListResponseInnerAddressQuestionnaire");
    FetchAddressVerificationListResponseInnerAddressQuestionnaire out;
    common::detail::json::read(obj, "sendTo", out.send_to);
    common::detail::json::read(obj, "satoshiToken", out.satoshi_token);
    common::detail::json::read(obj, "isAddressOwner", out.is_address_owner);
    common::detail::json::read(obj, "verifyMethod", out.verify_method);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchAddressVerificationListResponseInnerAddressQuestionnaire& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "sendTo", v.send_to);
    common::detail::json::write(obj, "satoshiToken", v.satoshi_token);
    common::detail::json::write(obj, "isAddressOwner", v.is_address_owner);
    common::detail::json::write(obj, "verifyMethod", v.verify_method);
}

} // namespace binance::wallet::rest_api
