//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/fiat_withdraw_response_data.hpp>

namespace binance::fiat::rest_api {

FiatWithdrawResponseData tag_invoke(boost::json::value_to_tag<FiatWithdrawResponseData> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FiatWithdrawResponseData");
    FiatWithdrawResponseData out;
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FiatWithdrawResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::fiat::rest_api
