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

struct FetchRsaPublicKeyResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::string> data;
    std::optional<bool> success;

    bool operator==(const FetchRsaPublicKeyResponse& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT FetchRsaPublicKeyResponse tag_invoke(
    boost::json::value_to_tag<FetchRsaPublicKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv,
                                         const FetchRsaPublicKeyResponse& v);

} // namespace binance::gift_card::rest_api
