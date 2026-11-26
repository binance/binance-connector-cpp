//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/gift_card/rest_api/models/redeem_a_binance_gift_card_response.hpp>

namespace binance::gift_card::rest_api {

RedeemABinanceGiftCardResponse
tag_invoke(boost::json::value_to_tag<RedeemABinanceGiftCardResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RedeemABinanceGiftCardResponse");
    RedeemABinanceGiftCardResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "data", out.data);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RedeemABinanceGiftCardResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "data", v.data);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::gift_card::rest_api
