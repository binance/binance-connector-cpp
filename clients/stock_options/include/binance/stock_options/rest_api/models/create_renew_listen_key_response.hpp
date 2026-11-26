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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct CreateRenewListenKeyResponse {
    /// User data stream session identifier.
    std::optional<std::string> listen_key;

    bool operator==(const CreateRenewListenKeyResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT CreateRenewListenKeyResponse tag_invoke(
    boost::json::value_to_tag<CreateRenewListenKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const CreateRenewListenKeyResponse& v);

} // namespace binance::stock_options::rest_api
