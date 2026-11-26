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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryLiquidationLoanResponse {
    /// The asset of the liquidation loan (USDC by default)
    std::optional<std::string> asset;
    /// Total liquidation loan amount
    std::optional<std::string> amount;
    /// Amount that has been repaid
    std::optional<std::string> repaid_amount;
    /// Outstanding amount remaining to be repaid
    std::optional<std::string> remaining_amount;

    bool operator==(const QueryLiquidationLoanResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryLiquidationLoanResponse tag_invoke(
    boost::json::value_to_tag<QueryLiquidationLoanResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryLiquidationLoanResponse& v);

} // namespace binance::margin_trading::rest_api
