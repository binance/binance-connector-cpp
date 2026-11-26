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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct BalanceUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Asset
    std::optional<std::string> a;
    /// Balance Delta
    std::optional<std::string> d;
    /// Clear Time
    std::optional<std::int64_t> t_uppercase;

    bool operator==(const BalanceUpdate& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT BalanceUpdate tag_invoke(boost::json::value_to_tag<BalanceUpdate> /*tag*/,
                                             const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const BalanceUpdate& v);

} // namespace binance::spot::websocket_api
