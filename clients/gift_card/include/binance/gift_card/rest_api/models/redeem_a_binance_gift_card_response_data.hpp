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

namespace binance::gift_card::rest_api {

struct RedeemABinanceGiftCardResponseData {
    std::optional<std::string> reference_no;
    std::optional<std::string> identity_no;
    std::optional<std::string> token;
    std::optional<std::string> amount;

    bool operator==(const RedeemABinanceGiftCardResponseData& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT RedeemABinanceGiftCardResponseData
tag_invoke(boost::json::value_to_tag<RedeemABinanceGiftCardResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv,
                                         const RedeemABinanceGiftCardResponseData& v);

} // namespace binance::gift_card::rest_api
