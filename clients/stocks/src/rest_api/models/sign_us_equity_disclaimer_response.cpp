//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/sign_us_equity_disclaimer_response.hpp>

namespace binance::stocks::rest_api {

SignUsEquityDisclaimerResponse
tag_invoke(boost::json::value_to_tag<SignUsEquityDisclaimerResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SignUsEquityDisclaimerResponse");
    SignUsEquityDisclaimerResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SignUsEquityDisclaimerResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::stocks::rest_api
