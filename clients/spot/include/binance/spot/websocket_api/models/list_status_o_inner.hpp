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

struct ListStatusOInner {
    /// Symbol
    std::optional<std::string> s;
    /// OrderId
    std::optional<std::int64_t> i;
    /// ClientOrderId
    std::optional<std::string> c;

    bool operator==(const ListStatusOInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ListStatusOInner tag_invoke(boost::json::value_to_tag<ListStatusOInner> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ListStatusOInner& v);

} // namespace binance::spot::websocket_api
