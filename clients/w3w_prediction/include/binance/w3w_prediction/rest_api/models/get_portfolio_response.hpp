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

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response_positions_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetPortfolioResponse {
    std::optional<std::string> chain_id;
    std::optional<std::string> wallet_address;
    std::optional<std::int64_t> active_positions_count;
    std::optional<std::string> total_realized_pnl;
    std::optional<std::string> total_unrealized_pnl;
    std::optional<std::string> total_pnl;
    std::optional<std::string> total_cost_basis;
    std::optional<std::string> total_current_value;
    std::optional<std::vector<GetPortfolioResponsePositionsInner>> positions;

    bool operator==(const GetPortfolioResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetPortfolioResponse
tag_invoke(boost::json::value_to_tag<GetPortfolioResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetPortfolioResponse& v);

} // namespace binance::w3w_prediction::rest_api
