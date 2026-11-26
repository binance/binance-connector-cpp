//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/gift_card/rest_api/models/verify_binance_gift_card_by_gift_card_number_response_data.hpp>

namespace binance::gift_card::rest_api {

VerifyBinanceGiftCardByGiftCardNumberResponseData
tag_invoke(boost::json::value_to_tag<VerifyBinanceGiftCardByGiftCardNumberResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "VerifyBinanceGiftCardByGiftCardNumberResponseData");
    VerifyBinanceGiftCardByGiftCardNumberResponseData out;
    common::detail::json::read(obj, "valid", out.valid);
    common::detail::json::read(obj, "token", out.token);
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VerifyBinanceGiftCardByGiftCardNumberResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "valid", v.valid);
    common::detail::json::write(obj, "token", v.token);
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::gift_card::rest_api
