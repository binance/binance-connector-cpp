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

struct AccountStatusResponse {
    std::optional<std::string> data;

    bool operator==(const AccountStatusResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AccountStatusResponse
tag_invoke(boost::json::value_to_tag<AccountStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountStatusResponse& v);

} // namespace binance::wallet::rest_api
