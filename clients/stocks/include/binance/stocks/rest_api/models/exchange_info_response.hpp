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

#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/exchange_info_response_symbols_inner.hpp>

namespace binance::stocks::rest_api {

struct ExchangeInfoResponse {
    /// Always `UTC`.
    std::optional<std::string> timezone;
    /// List of tradable symbols with trading rules.
    std::optional<std::vector<ExchangeInfoResponseSymbolsInner>> symbols;

    bool operator==(const ExchangeInfoResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT ExchangeInfoResponse
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const ExchangeInfoResponse& v);

} // namespace binance::stocks::rest_api
