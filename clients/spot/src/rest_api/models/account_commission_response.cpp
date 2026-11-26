//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/account_commission_response.hpp>

namespace binance::spot::rest_api {

AccountCommissionResponse tag_invoke(boost::json::value_to_tag<AccountCommissionResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountCommissionResponse");
    AccountCommissionResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "standardCommission", out.standard_commission);
    common::detail::json::read(obj, "specialCommission", out.special_commission);
    common::detail::json::read(obj, "taxCommission", out.tax_commission);
    common::detail::json::read(obj, "discount", out.discount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountCommissionResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "standardCommission", v.standard_commission);
    common::detail::json::write(obj, "specialCommission", v.special_commission);
    common::detail::json::write(obj, "taxCommission", v.tax_commission);
    common::detail::json::write(obj, "discount", v.discount);
}

} // namespace binance::spot::rest_api
