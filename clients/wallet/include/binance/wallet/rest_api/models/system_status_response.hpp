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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct SystemStatusResponse {
    /// 0: normal，1：system maintenance
    std::optional<std::int64_t> status;
    /// "normal", "system_maintenance"
    std::optional<std::string> msg;

    bool operator==(const SystemStatusResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT SystemStatusResponse
tag_invoke(boost::json::value_to_tag<SystemStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const SystemStatusResponse& v);

} // namespace binance::wallet::rest_api
