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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct CreateRenewListenKeyResponse {
    /// Session identifier for the stock user data stream.
    std::optional<std::string> listen_key;

    bool operator==(const CreateRenewListenKeyResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CreateRenewListenKeyResponse tag_invoke(
    boost::json::value_to_tag<CreateRenewListenKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CreateRenewListenKeyResponse& v);

} // namespace binance::stocks::rest_api
