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

struct GetPortfolioResponsePositionsInner {
    std::optional<std::int64_t> id;
    std::optional<std::string> wallet_address;
    std::optional<std::int64_t> market_topic_id;
    std::optional<std::int64_t> market_id;
    std::optional<std::string> token_id;
    std::optional<std::string> vendor;
    std::optional<std::string> current_shares;
    std::optional<std::string> avg_price;
    std::optional<std::string> current_price;
    std::optional<std::string> realized_pnl;
    std::optional<std::string> unrealized_pnl;
    std::optional<std::string> total_pnl;
    std::optional<std::string> pnl_percentage;
    std::optional<bool> is_resolved;

    bool operator==(const GetPortfolioResponsePositionsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetPortfolioResponsePositionsInner
tag_invoke(boost::json::value_to_tag<GetPortfolioResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetPortfolioResponsePositionsInner& v);

} // namespace binance::w3w_prediction::rest_api
