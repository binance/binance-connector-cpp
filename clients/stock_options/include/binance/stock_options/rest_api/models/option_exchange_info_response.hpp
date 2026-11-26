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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_exchange_info_response_symbols_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionExchangeInfoResponse {
    /// Always `UTC`.
    std::optional<std::string> timezone;
    /// Matched contract.
    std::optional<std::vector<OptionExchangeInfoResponseSymbolsInner>> symbols;

    bool operator==(const OptionExchangeInfoResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionExchangeInfoResponse tag_invoke(
    boost::json::value_to_tag<OptionExchangeInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionExchangeInfoResponse& v);

} // namespace binance::stock_options::rest_api
