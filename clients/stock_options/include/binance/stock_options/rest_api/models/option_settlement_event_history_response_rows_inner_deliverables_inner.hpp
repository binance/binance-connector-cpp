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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner {
    /// Present on cash legs only: `OPEXC` (exercise cash) / `OPASN` (assignment cash) / `OPCSH`
    /// (cash settlement).
    std::optional<std::string> type;
    /// Ticker for the share leg, currency for the cash leg.
    std::optional<std::string> symbol;
    /// Signed amount: positive = received, negative = paid. Number of shares for the share leg.
    std::optional<std::string> amount;

    bool operator==(const OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner& /*other*/)
        const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner
tag_invoke(boost::json::value_to_tag<
               OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner& v);

} // namespace binance::stock_options::rest_api
