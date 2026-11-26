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

struct OptionExchangeInfoResponseSymbolsInnerDeliverablesInner {
    /// `EQUITY` (shares; `symbol` is the ticker and `amount` is the number of shares) / `CASH`
    /// (`symbol` is the currency and `amount` is the cash amount).
    std::optional<std::string> type;
    /// Ticker or currency.
    std::optional<std::string> symbol;
    /// Number of shares or cash amount.
    std::optional<std::string> amount;

    bool operator==(
        const OptionExchangeInfoResponseSymbolsInnerDeliverablesInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionExchangeInfoResponseSymbolsInnerDeliverablesInner tag_invoke(
    boost::json::value_to_tag<OptionExchangeInfoResponseSymbolsInnerDeliverablesInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionExchangeInfoResponseSymbolsInnerDeliverablesInner& v);

} // namespace binance::stock_options::rest_api
