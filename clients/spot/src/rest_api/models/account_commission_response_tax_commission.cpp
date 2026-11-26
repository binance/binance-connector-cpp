//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/account_commission_response_tax_commission.hpp>

namespace binance::spot::rest_api {

AccountCommissionResponseTaxCommission
tag_invoke(boost::json::value_to_tag<AccountCommissionResponseTaxCommission> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountCommissionResponseTaxCommission");
    AccountCommissionResponseTaxCommission out;
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    common::detail::json::read(obj, "buyer", out.buyer);
    common::detail::json::read(obj, "seller", out.seller);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountCommissionResponseTaxCommission& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
    common::detail::json::write(obj, "buyer", v.buyer);
    common::detail::json::write(obj, "seller", v.seller);
}

} // namespace binance::spot::rest_api
