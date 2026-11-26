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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetOtcBlocktradeEventsResponseEventsInner {
    std::optional<std::string> event;
    std::optional<std::string> blocktrade_id;
    std::optional<std::string> order_id;
    std::optional<std::int64_t> market_id;
    std::optional<std::string> amount;
    std::optional<std::string> fee;
    std::optional<std::string> effective_fee;
    std::optional<std::string> price;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> transaction_hash;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> reason;
    std::optional<bool> is_maker;
    std::optional<std::string> timestamp;

    bool operator==(const GetOtcBlocktradeEventsResponseEventsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetOtcBlocktradeEventsResponseEventsInner
tag_invoke(boost::json::value_to_tag<GetOtcBlocktradeEventsResponseEventsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetOtcBlocktradeEventsResponseEventsInner& v);

} // namespace binance::w3w_prediction::rest_api
