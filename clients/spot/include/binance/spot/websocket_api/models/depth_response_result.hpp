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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct DepthResponseResult {
    std::optional<std::int64_t> last_update_id;
    /// Bid orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> bids;
    /// Ask orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> asks;

    bool operator==(const DepthResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT DepthResponseResult
tag_invoke(boost::json::value_to_tag<DepthResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const DepthResponseResult& v);

} // namespace binance::spot::websocket_api
