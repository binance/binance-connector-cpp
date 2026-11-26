//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/get_exchange_info_response_data_assets_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

GetExchangeInfoResponseDataAssetsInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetExchangeInfoResponseDataAssetsInner");
    GetExchangeInfoResponseDataAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetExchangeInfoResponseDataAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
}

} // namespace binance::alpha::rest_api
