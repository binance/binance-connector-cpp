//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/withdraw_response.hpp>

namespace binance::wallet::rest_api {

WithdrawResponse tag_invoke(boost::json::value_to_tag<WithdrawResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "WithdrawResponse");
    WithdrawResponse out;
    common::detail::json::read(obj, "id", out.id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const WithdrawResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
}

} // namespace binance::wallet::rest_api
