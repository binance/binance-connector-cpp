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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct DepositAddressResponse {
    std::optional<std::string> address;
    std::optional<std::string> coin;
    std::optional<std::string> tag;
    std::optional<std::string> url;

    bool operator==(const DepositAddressResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DepositAddressResponse
tag_invoke(boost::json::value_to_tag<DepositAddressResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DepositAddressResponse& v);

} // namespace binance::wallet::rest_api
