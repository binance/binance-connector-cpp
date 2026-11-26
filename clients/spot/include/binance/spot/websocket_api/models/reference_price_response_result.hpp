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

struct ReferencePriceResponseResult {
    std::optional<std::string> symbol;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> reference_price;
    /// Timestamp when the reference price was valid
    std::optional<std::int64_t> timestamp;
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;

    bool operator==(const ReferencePriceResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ReferencePriceResponseResult tag_invoke(
    boost::json::value_to_tag<ReferencePriceResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ReferencePriceResponseResult& v);

} // namespace binance::spot::websocket_api
