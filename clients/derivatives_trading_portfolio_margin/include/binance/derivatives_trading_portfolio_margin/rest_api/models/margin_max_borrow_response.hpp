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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct MarginMaxBorrowResponse {
    /// account's currently max borrowable amount with sufficient system availability
    std::optional<std::string> amount;
    /// max borrowable amount limited by the account level
    std::optional<std::string> borrow_limit;

    bool operator==(const MarginMaxBorrowResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginMaxBorrowResponse tag_invoke(
    boost::json::value_to_tag<MarginMaxBorrowResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginMaxBorrowResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
