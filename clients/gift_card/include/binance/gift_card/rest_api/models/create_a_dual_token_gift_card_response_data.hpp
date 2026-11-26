//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/gift_card/export.hpp>

namespace binance::gift_card::rest_api {

struct CreateADualTokenGiftCardResponseData {
    std::optional<std::string> reference_no;
    std::optional<std::string> code;
    std::optional<std::int64_t> expired_time;

    bool operator==(const CreateADualTokenGiftCardResponseData& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT CreateADualTokenGiftCardResponseData
tag_invoke(boost::json::value_to_tag<CreateADualTokenGiftCardResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv,
                                         const CreateADualTokenGiftCardResponseData& v);

} // namespace binance::gift_card::rest_api
