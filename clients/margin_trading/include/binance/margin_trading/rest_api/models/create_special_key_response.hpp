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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct CreateSpecialKeyResponse {
    /// api Key.
    std::optional<std::string> api_key;
    /// secretKey will be null when creating an RSA key
    std::optional<std::string> secret_key;
    /// HMAC_SHA256 or RSA
    std::optional<std::string> type;

    bool operator==(const CreateSpecialKeyResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT CreateSpecialKeyResponse tag_invoke(
    boost::json::value_to_tag<CreateSpecialKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const CreateSpecialKeyResponse& v);

} // namespace binance::margin_trading::rest_api
