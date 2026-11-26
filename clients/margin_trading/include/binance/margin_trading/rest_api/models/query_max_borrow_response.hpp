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

struct QueryMaxBorrowResponse {
    /// account's currently max borrowable amount with sufficient system availability
    std::optional<std::string> amount;
    /// max borrowable amount limited by the account level
    std::optional<std::string> borrow_limit;

    bool operator==(const QueryMaxBorrowResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMaxBorrowResponse
tag_invoke(boost::json::value_to_tag<QueryMaxBorrowResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMaxBorrowResponse& v);

} // namespace binance::margin_trading::rest_api
