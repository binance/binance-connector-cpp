//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/exchange_info_response.hpp>

namespace binance::stocks::rest_api {

ExchangeInfoResponse tag_invoke(boost::json::value_to_tag<ExchangeInfoResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInfoResponse");
    ExchangeInfoResponse out;
    common::detail::json::read(obj, "timezone", out.timezone);
    common::detail::json::read(obj, "symbols", out.symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "timezone", v.timezone);
    common::detail::json::write(obj, "symbols", v.symbols);
}

} // namespace binance::stocks::rest_api
