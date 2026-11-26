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

struct QueryPnLResponse {
    std::optional<std::string> chain_id;
    std::optional<std::string> wallet_address;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<boost::json::value>> pnl;
    std::optional<std::vector<GetPortfolioResponsePositionsInner>> pnl_list;
    std::optional<std::int64_t> total_count;
    std::optional<std::string> total_realized_pnl;
    std::optional<std::string> total_unrealized_pnl;
    std::optional<std::string> total_pnl;

    bool operator==(const QueryPnLResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPnLResponse
tag_invoke(boost::json::value_to_tag<QueryPnLResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, const QueryPnLResponse& v);

} // namespace binance::w3w_prediction::rest_api
