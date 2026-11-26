//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/deposit_response.hpp>

namespace binance::fiat::rest_api {

DepositResponse tag_invoke(boost::json::value_to_tag<DepositResponse> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DepositResponse");
    DepositResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DepositResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::fiat::rest_api
