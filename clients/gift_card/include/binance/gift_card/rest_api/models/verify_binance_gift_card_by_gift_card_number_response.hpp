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
#include <binance/gift_card/rest_api/models/verify_binance_gift_card_by_gift_card_number_response_data.hpp>

namespace binance::gift_card::rest_api {

struct VerifyBinanceGiftCardByGiftCardNumberResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<VerifyBinanceGiftCardByGiftCardNumberResponseData> data;
    std::optional<bool> success;

    bool operator==(const VerifyBinanceGiftCardByGiftCardNumberResponse& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT VerifyBinanceGiftCardByGiftCardNumberResponse
tag_invoke(boost::json::value_to_tag<VerifyBinanceGiftCardByGiftCardNumberResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv,
                                         const VerifyBinanceGiftCardByGiftCardNumberResponse& v);

} // namespace binance::gift_card::rest_api
