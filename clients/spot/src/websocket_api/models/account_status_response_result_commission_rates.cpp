//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/account_status_response_result_commission_rates.hpp>

namespace binance::spot::websocket_api {

AccountStatusResponseResultCommissionRates
tag_invoke(boost::json::value_to_tag<AccountStatusResponseResultCommissionRates> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountStatusResponseResultCommissionRates");
    AccountStatusResponseResultCommissionRates out;
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    common::detail::json::read(obj, "buyer", out.buyer);
    common::detail::json::read(obj, "seller", out.seller);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountStatusResponseResultCommissionRates& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
    common::detail::json::write(obj, "buyer", v.buyer);
    common::detail::json::write(obj, "seller", v.seller);
}

} // namespace binance::spot::websocket_api
