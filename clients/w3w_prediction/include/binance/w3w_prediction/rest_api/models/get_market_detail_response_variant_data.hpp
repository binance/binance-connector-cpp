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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetMarketDetailResponseVariantData {
    std::optional<std::string> type;
    std::optional<std::string> start_price;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> end_price;
    std::optional<std::string> price_feed_id;
    std::optional<std::string> price_feed_provider;
    std::optional<std::string> price_feed_symbol;

    bool operator==(const GetMarketDetailResponseVariantData& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetMarketDetailResponseVariantData
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseVariantData> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetMarketDetailResponseVariantData& v);

} // namespace binance::w3w_prediction::rest_api
