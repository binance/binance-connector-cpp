//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/trade_fee_response_inner.hpp>

namespace binance::wallet::rest_api {

TradeFeeResponseInner tag_invoke(boost::json::value_to_tag<TradeFeeResponseInner> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradeFeeResponseInner");
    TradeFeeResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "makerCommission", out.maker_commission);
    common::detail::json::read(obj, "takerCommission", out.taker_commission);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradeFeeResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "makerCommission", v.maker_commission);
    common::detail::json::write(obj, "takerCommission", v.taker_commission);
}

} // namespace binance::wallet::rest_api
