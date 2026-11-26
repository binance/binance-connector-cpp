//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_exchange_info_response.hpp>

namespace binance::stock_options::rest_api {

OptionExchangeInfoResponse tag_invoke(boost::json::value_to_tag<OptionExchangeInfoResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionExchangeInfoResponse");
    OptionExchangeInfoResponse out;
    common::detail::json::read(obj, "timezone", out.timezone);
    common::detail::json::read(obj, "symbols", out.symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionExchangeInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "timezone", v.timezone);
    common::detail::json::write(obj, "symbols", v.symbols);
}

} // namespace binance::stock_options::rest_api
