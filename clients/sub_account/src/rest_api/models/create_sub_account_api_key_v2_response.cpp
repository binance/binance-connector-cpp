//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/create_sub_account_api_key_v2_response.hpp>

namespace binance::sub_account::rest_api {

CreateSubAccountApiKeyV2Response
tag_invoke(boost::json::value_to_tag<CreateSubAccountApiKeyV2Response> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateSubAccountApiKeyV2Response");
    CreateSubAccountApiKeyV2Response out;
    common::detail::json::read(obj, "apiName", out.api_name);
    common::detail::json::read(obj, "apiKey", out.api_key);
    common::detail::json::read(obj, "secretKey", out.secret_key);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canMarginLoanRepay", out.can_margin_loan_repay);
    common::detail::json::read(obj, "canFuturesTrade", out.can_futures_trade);
    common::detail::json::read(obj, "canUniversalTransfer", out.can_universal_transfer);
    common::detail::json::read(obj, "canVanillaOptions", out.can_vanilla_options);
    common::detail::json::read(obj, "canFixApiTrading", out.can_fix_api_trading);
    common::detail::json::read(obj, "canFixApiReading", out.can_fix_api_reading);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "ipList", out.ip_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateSubAccountApiKeyV2Response& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "apiName", v.api_name);
    common::detail::json::write(obj, "apiKey", v.api_key);
    common::detail::json::write(obj, "secretKey", v.secret_key);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canMarginLoanRepay", v.can_margin_loan_repay);
    common::detail::json::write(obj, "canFuturesTrade", v.can_futures_trade);
    common::detail::json::write(obj, "canUniversalTransfer", v.can_universal_transfer);
    common::detail::json::write(obj, "canVanillaOptions", v.can_vanilla_options);
    common::detail::json::write(obj, "canFixApiTrading", v.can_fix_api_trading);
    common::detail::json::write(obj, "canFixApiReading", v.can_fix_api_reading);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "ipList", v.ip_list);
}

} // namespace binance::sub_account::rest_api
