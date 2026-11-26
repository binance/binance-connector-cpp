//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/gift_card/export.hpp>
#include <binance/gift_card/rest_api/models/redeem_a_binance_gift_card_response_data.hpp>

namespace binance::gift_card::rest_api {

struct RedeemABinanceGiftCardResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<RedeemABinanceGiftCardResponseData> data;
    std::optional<bool> success;

    bool operator==(const RedeemABinanceGiftCardResponse& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT RedeemABinanceGiftCardResponse
tag_invoke(boost::json::value_to_tag<RedeemABinanceGiftCardResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv,
                                         const RedeemABinanceGiftCardResponse& v);

} // namespace binance::gift_card::rest_api
