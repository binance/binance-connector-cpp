//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/exchange_info_response_sors_inner.hpp>

namespace binance::spot::websocket_api {

ExchangeInfoResponseSorsInner
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponseSorsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInfoResponseSorsInner");
    ExchangeInfoResponseSorsInner out;
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "symbols", out.symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInfoResponseSorsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "symbols", v.symbols);
}

} // namespace binance::spot::websocket_api
