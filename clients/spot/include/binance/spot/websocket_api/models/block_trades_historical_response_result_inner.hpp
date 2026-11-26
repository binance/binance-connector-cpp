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

struct BlockTradesHistoricalResponseResultInner {
    std::optional<std::int64_t> id;
    std::optional<std::string> price;
    std::optional<std::string> qty;
    std::optional<std::string> quote_qty;
    std::optional<std::int64_t> time;
    std::optional<bool> is_buyer_maker;

    bool operator==(const BlockTradesHistoricalResponseResultInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT BlockTradesHistoricalResponseResultInner
tag_invoke(boost::json::value_to_tag<BlockTradesHistoricalResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const BlockTradesHistoricalResponseResultInner& v);

} // namespace binance::spot::websocket_api
