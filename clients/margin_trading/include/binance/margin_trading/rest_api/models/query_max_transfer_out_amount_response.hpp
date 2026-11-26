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

struct QueryMaxTransferOutAmountResponse {
    /// amount.
    std::optional<std::string> amount;

    bool operator==(const QueryMaxTransferOutAmountResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMaxTransferOutAmountResponse
tag_invoke(boost::json::value_to_tag<QueryMaxTransferOutAmountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMaxTransferOutAmountResponse& v);

} // namespace binance::margin_trading::rest_api
