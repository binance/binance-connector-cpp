//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/fiat_withdraw_request_account_info.hpp>

namespace binance::fiat::rest_api {

FiatWithdrawRequestAccountInfo
tag_invoke(boost::json::value_to_tag<FiatWithdrawRequestAccountInfo> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FiatWithdrawRequestAccountInfo");
    FiatWithdrawRequestAccountInfo out;
    common::detail::json::read(obj, "accountNumber", out.account_number);
    common::detail::json::read(obj, "agency", out.agency);
    common::detail::json::read(obj, "bankCodeForPix", out.bank_code_for_pix);
    common::detail::json::read(obj, "accountType", out.account_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FiatWithdrawRequestAccountInfo& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "accountNumber", v.account_number);
    common::detail::json::write(obj, "agency", v.agency);
    common::detail::json::write(obj, "bankCodeForPix", v.bank_code_for_pix);
    common::detail::json::write(obj, "accountType", v.account_type);
}

} // namespace binance::fiat::rest_api
