//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/models/check_dual_investment_accounts_response.hpp>

namespace binance::dual_investment::rest_api {

CheckDualInvestmentAccountsResponse
tag_invoke(boost::json::value_to_tag<CheckDualInvestmentAccountsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CheckDualInvestmentAccountsResponse");
    CheckDualInvestmentAccountsResponse out;
    common::detail::json::read(obj, "totalAmountInBTC", out.total_amount_in_btc);
    common::detail::json::read(obj, "totalAmountInUSDT", out.total_amount_in_usdt);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CheckDualInvestmentAccountsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAmountInBTC", v.total_amount_in_btc);
    common::detail::json::write(obj, "totalAmountInUSDT", v.total_amount_in_usdt);
}

} // namespace binance::dual_investment::rest_api
