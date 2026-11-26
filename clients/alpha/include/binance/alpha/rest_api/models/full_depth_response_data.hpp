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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

/// Order book data.
struct FullDepthResponseData {
    /// Last order book update ID.
    std::optional<std::int64_t> last_update_id;
    /// Trading pair symbol.
    std::optional<std::string> symbol;
    /// Bid orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> bids;
    /// Ask orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> asks;
    /// Event time in milliseconds.
    std::optional<std::int64_t> e_uppercase;
    /// Transaction time in milliseconds.
    std::optional<std::int64_t> t_uppercase;

    bool operator==(const FullDepthResponseData& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT FullDepthResponseData
tag_invoke(boost::json::value_to_tag<FullDepthResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const FullDepthResponseData& v);

} // namespace binance::alpha::rest_api
