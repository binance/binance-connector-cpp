//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner.hpp>

namespace binance::wallet::rest_api {

FetchAddressVerificationListResponseInner
tag_invoke(boost::json::value_to_tag<FetchAddressVerificationListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "FetchAddressVerificationListResponseInner");
    FetchAddressVerificationListResponseInner out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "token", out.token);
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "addressQuestionnaire", out.address_questionnaire);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchAddressVerificationListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "token", v.token);
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "addressQuestionnaire", v.address_questionnaire);
}

} // namespace binance::wallet::rest_api
