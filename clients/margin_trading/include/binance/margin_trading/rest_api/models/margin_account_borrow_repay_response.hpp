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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountBorrowRepayResponse {
    /// tran Id.
    std::optional<std::int64_t> tran_id;

    bool operator==(const MarginAccountBorrowRepayResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountBorrowRepayResponse
tag_invoke(boost::json::value_to_tag<MarginAccountBorrowRepayResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const MarginAccountBorrowRepayResponse& v);

} // namespace binance::margin_trading::rest_api
