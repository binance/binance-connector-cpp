//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/get_exchange_info_response_data.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

GetExchangeInfoResponseData
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetExchangeInfoResponseData");
    GetExchangeInfoResponseData out;
    common::detail::json::read(obj, "timezone", out.timezone);
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "symbols", out.symbols);
    common::detail::json::read(obj, "orderTypes", out.order_types);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetExchangeInfoResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "timezone", v.timezone);
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "symbols", v.symbols);
    common::detail::json::write(obj, "orderTypes", v.order_types);
}

} // namespace binance::alpha::rest_api
